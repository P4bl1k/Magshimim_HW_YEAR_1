#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "raygui.h"
#include "raylib.h"
#include "Gui.h"
#include "View.h"
#include "LinkedList.h"

PopupState currentPopup = NO_POPUP;
FrameNode* head = NULL;

static FrameNode* currentPlayFrame = NULL;
static double lastFrameSwitchTime = 0;
static Texture2D currentPlaybackTexture = {0}; 
static bool playbackTextureLoaded = false;
static int playbackRepeatCount = 0;

int main(void)
{
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "GIFMaker");
    SetTargetFPS(60);

    char* title = "GIFMaker";
    int fontSize = 60;

    char *mainButtonText[NUM_MAIN_BUTTONS] = {
        "Add Frame",
        "Remove Frame",
        "Move Frame",
        "Set Frame Duration",
        "Set All Durations",
        "List Frames",
        "Play GIF",
    };

    int startY = (screenHeight - (NUM_MAIN_BUTTONS * (BUTTON_HEIGHT + 10))) / 2;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE); 

        if (currentPopup == NO_POPUP)
        {
            drawMainMenu(screenWidth, screenHeight, title, fontSize, mainButtonText, startY);
        }
        else
        {
            // Draw the overlay for popups
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(RAYWHITE, 0.5f));
            Rectangle panel = { 200, 180, 400, 260 };
            DrawRectangleRec(panel, LIGHTGRAY);
            DrawRectangleLinesEx(panel, 2, DARKGRAY);
            float btnWidth = 90;
            float btnHeight = 30;
            float spacing = 10;

            switch (currentPopup)
            {
                case ADD_FRAME_POPUP:
                    drawAddFramePopup(panel, btnWidth, btnHeight, spacing);
                    break;
                case REMOVE_FRAME_POPUP:
                    drawRemoveFramePopup(panel, btnWidth, btnHeight, spacing);
                    break;
                case MOVE_FRAME_POPUP:
                    drawMoveFramePopup(panel, btnWidth, btnHeight, spacing);
                    break;
                case CHANGE_DURATION_POPUP:
                    drawChangeDurationPopup(panel, btnWidth, btnHeight, spacing);
                    break;
                case CHANGE_ALL_DURATIONS_POPUP:
                    drawChangeAllDurationsPopup(panel, btnWidth, btnHeight, spacing);
                    break;
                case LIST_FRAMES_DISPLAY:
                    drawListFramesDisplay(panel, btnWidth, btnHeight);
                    break;
                case SAVE_PROJECT_POPUP:
                    drawSaveProjectPopup(panel, btnWidth, btnHeight, spacing);
                    break;
                case LOAD_PROJECT_POPUP:
                    drawLoadProjectPopup(panel, btnWidth, btnHeight, spacing);
                    break;

                case PLAYBACK_MODE:
                {
                    if (currentPlayFrame == NULL)
                    {
                        currentPlayFrame = head;
                        playbackRepeatCount = 0;
                        lastFrameSwitchTime = GetTime();

                        if (currentPlayFrame == NULL || currentPlayFrame->frame == NULL)
                        {
                            currentPopup = NO_POPUP; // Nothing to play, exit playback
                            break; // Exit this switch case
                        }
                    }

                    if (!playbackTextureLoaded && currentPlayFrame != NULL && currentPlayFrame->frame != NULL)
                    {
                        Image img = LoadImage(currentPlayFrame->frame->path);
                        if (img.data != NULL)
                        {
                            currentPlaybackTexture = LoadTextureFromImage(img);
                            UnloadImage(img);
                            playbackTextureLoaded = true;
                        }
                        else
                        {
                            printf("Warning: Could not load image '%s' for frame '%s'. Skipping this frame.\n",
                                   currentPlayFrame->frame->path, currentPlayFrame->frame->name);
                            currentPlayFrame = currentPlayFrame->next;
                            lastFrameSwitchTime = GetTime(); 
                            if (currentPlayFrame == NULL) 
                            {
                                #ifdef GIF_REPEAT
                                if (GIF_REPEAT == 0 || playbackRepeatCount < GIF_REPEAT - 1) 
                                {
                                    currentPlayFrame = head;
                                    playbackRepeatCount++;
                                    if (currentPlayFrame == NULL || currentPlayFrame->frame == NULL) 
                                    {
                                        currentPopup = NO_POPUP;
                                    }
                                } 
                                else 
                                {
                                    currentPopup = NO_POPUP;
                                }
                                #else
                                currentPopup = NO_POPUP;
                                #endif
                            }
                            break; 
                        }
                    }
                    if (currentPlayFrame != NULL && playbackTextureLoaded)
                    {
                        ClearBackground(BLACK); 
                        int posX = (GetScreenWidth() - currentPlaybackTexture.width) / 2;
                        int posY = (GetScreenHeight() - currentPlaybackTexture.height) / 2;
                        DrawTexture(currentPlaybackTexture, posX, posY, WHITE);
                    }

                    if (currentPlayFrame != NULL && GetTime() - lastFrameSwitchTime >= (double)currentPlayFrame->frame->duration / 1000.0f)
                    {
                        if (playbackTextureLoaded)
                        {
                            UnloadTexture(currentPlaybackTexture);
                            playbackTextureLoaded = false;
                        }

                        currentPlayFrame = currentPlayFrame->next; 

                        if (currentPlayFrame == NULL)
                        {
                            #ifdef GIF_REPEAT
                            if (GIF_REPEAT == 0 || playbackRepeatCount < GIF_REPEAT - 1)
                            {
                                currentPlayFrame = head; 
                                playbackRepeatCount++;
                                if (currentPlayFrame == NULL || currentPlayFrame->frame == NULL) 
                                {
                                    currentPopup = NO_POPUP;
                                }
                            }
                            else
                            {
                                currentPopup = NO_POPUP; 
                            }
                            #else
                            currentPopup = NO_POPUP; 
                            #endif
                        }

                        lastFrameSwitchTime = GetTime(); 
                    }
                    if ((currentPlayFrame == NULL && currentPopup == PLAYBACK_MODE)) 
                    {
                        if (playbackTextureLoaded) UnloadTexture(currentPlaybackTexture);
                        currentPlayFrame = NULL;
                        lastFrameSwitchTime = 0;
                        currentPlaybackTexture = (Texture2D){0};
                        playbackTextureLoaded = false;
                        playbackRepeatCount = 0;
                        currentPopup = NO_POPUP; 
                    }
                    break; 
                }
            }
        }
        EndDrawing();
    }
    deletelist(&head);
    CloseWindow();
    return 0;
}