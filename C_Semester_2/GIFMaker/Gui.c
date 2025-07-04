#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h" 
#include "View.h"    
#include "raygui.h"

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40
#define NUM_MAIN_BUTTONS 7
#define MAX_INPUT_LEN 256
#define MAX_STR_LEN 64

// Global variables 
extern PopupState currentPopup;
extern FrameNode* head;
char inputBuffer[MAX_INPUT_LEN] = "";
char framePathInput[MAX_STR_LEN] = "";
char frameNameInput[MAX_STR_LEN] = "";
char frameNameToModify[MAX_STR_LEN] = "";
int frameDurationInput = 0;
int newFrameIndexInput = 0;
char projectFilePathInput[MAX_STR_LEN * 2] = "";
char projectFileNameInput[MAX_STR_LEN] = "";
char listFramesOutput[2048] = "";

bool pathEditMode = false;
bool nameEditMode = false;
bool durationEditMode = false;
bool indexEditMode = false;
bool filenameEditMode = false;

//---------------------------------------------------functions---------------------------------------------------//
Rectangle calculateListFramesPanelDimensions(char* listFramesOutput, float btnWidth, float btnHeight, int screenWidth, int screenHeight)
{
    int titleFontSize = 20;
    int contentFontSize = 16;
    int titleOffset = 10;
    int contentXOffset = 20;
    int contentYOffset = 40;
    int lineHeight = 20;
    int btnMargin = 10; 

    Vector2 titleTextSize = MeasureTextEx(GetFontDefault(), "Current Frames:", (float)titleFontSize, 0); 

    float maxContentTextWidth = 0;
    int totalContentTextHeight = 0;

    char listFramesOutputCopy[1024]; 
    strcpy(listFramesOutputCopy, listFramesOutput);

    char* line = strtok(listFramesOutputCopy, "\n");
    int lineCount = 0;
    while (line != NULL) 
    {
        Vector2 lineTextSize = MeasureTextEx(GetFontDefault(), line, (float)contentFontSize, 0);
        if (lineTextSize.x > maxContentTextWidth) 
        {
            maxContentTextWidth = lineTextSize.x;
        }
        totalContentTextHeight += lineHeight; 
        lineCount++;
        line = strtok(NULL, "\n");
    }

    float requiredWidth = titleTextSize.x + titleOffset + 10;
    if (maxContentTextWidth + contentXOffset + 10 > requiredWidth) 
    { 
        requiredWidth = maxContentTextWidth + contentXOffset + 10;
    }
    if (requiredWidth < btnWidth + (2 * btnMargin)) 
    {
        requiredWidth = btnWidth + (2 * btnMargin) + 20; 
    }

    float calculatedContentHeight = (float)contentYOffset + (lineCount * lineHeight); 
    float requiredHeight = calculatedContentHeight + btnHeight + btnMargin + 20; 

    Rectangle calculatedPanel = {0, 0, 0, 0};
    calculatedPanel.width = (int)requiredWidth;
    calculatedPanel.height = (int)requiredHeight;

    // Center the panel on the screen
    calculatedPanel.x = (screenWidth - calculatedPanel.width) / 2;
    calculatedPanel.y = (screenHeight - calculatedPanel.height) / 2;

    return calculatedPanel;
}
void processInput(char* buffer, int maxLen, bool* editMode, Rectangle textboxRect) 
{
    int key = 0;
    int len = 0;
    if (GuiTextBox(textboxRect, buffer, maxLen, *editMode)) 
    {
        *editMode = !(*editMode); // Toggle edit mode if clicked
    }

    if (*editMode) 
    {
        int key = GetCharPressed();
        while (key > 0) 
        {
            if ((key >= 32) && (key <= 125) && (strlen(buffer) < maxLen - 1)) 
            {
                strncat(buffer, (char*)&key, 1);
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) 
        {
            int len = strlen(buffer);
            if (len > 0) 
            {
                buffer[len - 1] = '\0';
            }
        }
    }
}

void drawAddFramePopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Add New Frame", panel.x + 10, panel.y + 10, 20, DARKGRAY);

    DrawText("Path:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle pathTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(framePathInput, MAX_STR_LEN, &pathEditMode, pathTextbox);

    DrawText("Name:", panel.x + 20, panel.y + 115, 18, GRAY);
    Rectangle nameTextbox = { panel.x + 20, panel.y + 140, panel.width - 40, 30 };
    processInput(frameNameInput, MAX_STR_LEN, &nameEditMode, nameTextbox);

    DrawText("Duration:", panel.x + 20, panel.y + 180, 18, GRAY);
    Rectangle durationTextbox = { panel.x + 20, panel.y + 205, panel.width - 40, 30 };
    processInput(inputBuffer, MAX_INPUT_LEN, &durationEditMode, durationTextbox);
    
    // Convert duration input when Enter is pressed or confirm button is clicked
    if (IsKeyPressed(KEY_ENTER)) 
    {
        frameDurationInput = atoi(inputBuffer);
    }

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 250, btnWidth, btnHeight }, "Confirm")) 
    {
        if (strlen(framePathInput) > 0 && strlen(frameNameInput) > 0 && inputBuffer[0] != '\0') 
        {
            int tempDuration = atoi(inputBuffer);
            if (tempDuration > 0) 
            {
                addNewFrame(&head, framePathInput, frameNameInput, tempDuration);
                currentPopup = NO_POPUP;
                // Clear inputs
                framePathInput[0] = '\0';
                frameNameInput[0] = '\0';
                frameDurationInput = 0; // Reset integer value
                inputBuffer[0] = '\0';
                pathEditMode = false; // Reset edit modes
                nameEditMode = false;
                durationEditMode = false;
            } 
            else 
            {
                printf("Error: Duration must be a positive number!\n");
            }
        } 
        else 
        {
            printf("Error: Missing fields for Add Frame! Path, Name, and Duration are required.\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 250, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        framePathInput[0] = '\0';
        frameNameInput[0] = '\0';
        frameDurationInput = 0; // Reset integer value
        inputBuffer[0] = '\0';
        pathEditMode = false; // Reset edit modes
        nameEditMode = false;
        durationEditMode = false;
    }
}

void drawRemoveFramePopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Remove Frame", panel.x + 10, panel.y + 10, 20, DARKGRAY);
    DrawText("Frame Name:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle nameTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(frameNameToModify, MAX_STR_LEN, &nameEditMode, nameTextbox);

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 130, btnWidth, btnHeight }, "Confirm")) 
    {
        if (strlen(frameNameToModify) > 0) 
        {
            removeFrame(&head, frameNameToModify);
            currentPopup = NO_POPUP;
            frameNameToModify[0] = '\0';
            nameEditMode = false; // Reset edit mode
        } 
        else 
        {
            printf("Error: Enter frame name to remove!\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 130, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        frameNameToModify[0] = '\0';
        nameEditMode = false; // Reset edit mode
    }
}

void drawMoveFramePopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Move Frame", panel.x + 10, panel.y + 10, 20, DARKGRAY);
    DrawText("Frame Name:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle nameTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(frameNameToModify, MAX_STR_LEN, &nameEditMode, nameTextbox);

    DrawText("New Index:", panel.x + 20, panel.y + 115, 18, GRAY);
    Rectangle indexTextbox = { panel.x + 20, panel.y + 140, panel.width - 40, 30 };
    processInput(inputBuffer, MAX_INPUT_LEN, &indexEditMode, indexTextbox);
    
    if (IsKeyPressed(KEY_ENTER)) 
    {
        newFrameIndexInput = atoi(inputBuffer);
    }

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 190, btnWidth, btnHeight }, "Confirm")) 
    {
        if (strlen(frameNameToModify) > 0 && inputBuffer[0] != '\0') 
        {
            int tempIndex = atoi(inputBuffer);
            if (tempIndex >= 0) 
            {
                changeFrameIndex(&head, frameNameToModify, tempIndex);
                currentPopup = NO_POPUP;
                frameNameToModify[0] = '\0';
                newFrameIndexInput = 0; // Reset integer value
                inputBuffer[0] = '\0';
                nameEditMode = false; // Reset edit modes
                indexEditMode = false;
            } 
            else 
            {
                printf("Error: New index must be a non-negative number!\n");
            }
        } 
        else 
        {
            printf("Error: Enter frame name and valid index!\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 190, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        frameNameToModify[0] = '\0';
        newFrameIndexInput = 0; // Reset integer value
        inputBuffer[0] = '\0';
        nameEditMode = false; // Reset edit modes
        indexEditMode = false;
    }
}

void drawChangeDurationPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Change Frame Duration", panel.x + 10, panel.y + 10, 20, DARKGRAY);
    DrawText("Frame Name:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle nameTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(frameNameToModify, MAX_STR_LEN, &nameEditMode, nameTextbox);

    DrawText("New Duration:", panel.x + 20, panel.y + 115, 18, GRAY);
    Rectangle durationTextbox = { panel.x + 20, panel.y + 140, panel.width - 40, 30 };
    processInput(inputBuffer, MAX_INPUT_LEN, &durationEditMode, durationTextbox);
    
    if (IsKeyPressed(KEY_ENTER)) 
    {
        frameDurationInput = atoi(inputBuffer);
    }

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 190, btnWidth, btnHeight }, "Confirm")) 
    {
        if (strlen(frameNameToModify) > 0 && inputBuffer[0] != '\0') 
        {
            int tempDuration = atoi(inputBuffer);
            if (tempDuration > 0) 
            {
                changeFrameDuration(&head, frameNameToModify, tempDuration);
                currentPopup = NO_POPUP;
                frameNameToModify[0] = '\0';
                frameDurationInput = 0; // Reset integer value
                inputBuffer[0] = '\0';
                nameEditMode = false; // Reset edit modes
                durationEditMode = false;
            } 
            else 
            {
                printf("Error: New duration must be a positive number!\n");
            }
        } 
        else 
        {
            printf("Error: Enter frame name and valid duration!\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 190, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        frameNameToModify[0] = '\0';
        frameDurationInput = 0; // Reset integer value
        inputBuffer[0] = '\0';
        nameEditMode = false; // Reset edit modes
        durationEditMode = false;
    }
}

void drawChangeAllDurationsPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Change All Durations", panel.x + 10, panel.y + 10, 20, DARKGRAY);
    DrawText("New Duration for All:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle durationTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(inputBuffer, MAX_INPUT_LEN, &durationEditMode, durationTextbox);
    
    if (IsKeyPressed(KEY_ENTER)) 
    {
        frameDurationInput = atoi(inputBuffer);
    }

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 130, btnWidth, btnHeight }, "Confirm")) 
    {
        if (inputBuffer[0] != '\0') 
        {
            int tempDuration = atoi(inputBuffer);
            if (tempDuration > 0) 
            {
                changeDurationForAll(&head, tempDuration);
                currentPopup = NO_POPUP;
                frameDurationInput = 0; // Reset integer value
                inputBuffer[0] = '\0';
                durationEditMode = false; // Reset edit mode
            } 
            else 
            {
                printf("Error: Enter a valid positive duration!\n");
            }
        } 
        else 
        {
            printf("Error: Enter a valid duration!\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 130, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        frameDurationInput = 0; // Reset integer value
        inputBuffer[0] = '\0';
        durationEditMode = false; // Reset edit mode
    }
}

void drawListFramesDisplay(Rectangle panel, float btnWidth, float btnHeight)
{

    float extraWidth = 240;
    float extraHeight = 120;
    Rectangle bigPanel = panel;
    bigPanel.x -= extraWidth / 2;
    bigPanel.y -= extraHeight / 2;
    bigPanel.width += extraWidth;
    bigPanel.height += extraHeight;

    DrawRectangleRec(bigPanel, LIGHTGRAY);
    DrawRectangleLinesEx(bigPanel, 2, DARKGRAY); 

    DrawText("Current Frames:", bigPanel.x + 10, bigPanel.y + 10, 20, DARKGRAY);

    int lineHeight = 20;
    int y = bigPanel.y + 40;
    
    char listFramesOutputCopyForDrawing[sizeof(listFramesOutput)];
    strncpy(listFramesOutputCopyForDrawing, listFramesOutput, sizeof(listFramesOutputCopyForDrawing) - 1);
    listFramesOutputCopyForDrawing[sizeof(listFramesOutputCopyForDrawing) - 1] = '\0';

    char* line = strtok(listFramesOutputCopyForDrawing, "\n");
    while (line != NULL) 
    {
        DrawText(line, bigPanel.x + 20, y, 16, BLACK);
        y += lineHeight;
        line = strtok(NULL, "\n");
    }

    if (GuiButton((Rectangle){ bigPanel.x + bigPanel.width/2 - btnWidth/2, bigPanel.y + bigPanel.height - btnHeight + 50, btnWidth, btnHeight }, "Close"))
    {
        currentPopup = NO_POPUP;
        listFramesOutput[0] = '\0'; 
    }
}

void drawMainMenu(int screenWidth, int screenHeight, char* title, int fontSize, char *mainButtonText[], int startY) 
{
    DrawText(title, (screenWidth - MeasureText(title, fontSize)) / 2, 40, fontSize, DARKBLUE);

    for (int i = 0; i < NUM_MAIN_BUTTONS; i++) 
    {
        int btnX = (screenWidth - BUTTON_WIDTH) / 2;
        int btnY = startY + i * (BUTTON_HEIGHT + 10);
        Rectangle btnRect = { btnX, btnY, BUTTON_WIDTH, BUTTON_HEIGHT };

        if (GuiButton(btnRect, mainButtonText[i])) 
        {
            switch (i) 
            {
                case 0: currentPopup = ADD_FRAME_POPUP; break;
                case 1: currentPopup = REMOVE_FRAME_POPUP; break;
                case 2: currentPopup = MOVE_FRAME_POPUP; break;
                case 3: currentPopup = CHANGE_DURATION_POPUP; break;
                case 4: currentPopup = CHANGE_ALL_DURATIONS_POPUP; break;
                case 5: // List Frames
                    currentPopup = LIST_FRAMES_DISPLAY;
                    strcpy(listFramesOutput, ""); // Clear previous content
                    FrameNode* current = head;
                    if (current == NULL) 
                    {
                        strcat(listFramesOutput, "No frames to list.\n");
                    } 
                    else 
                    {
                        char tempLine[MAX_STR_LEN * 3 + 100]; // Increased size for safety
                        while (current != NULL) 
                        {
                            snprintf(tempLine, sizeof(tempLine), "Name: %s, Duration: %d, Path: %s\n",
                                     current->frame->name, current->frame->duration, current->frame->path);
                            strcat(listFramesOutput, tempLine);
                            current = current->next;
                        }
                    }
                    break;
                case 6: // Play GIF
                    playGIF(&head); 
                    break;
            }
        }
    }
    // Add Save/Load buttons to the main menu
    int saveLoadY = startY + NUM_MAIN_BUTTONS * (BUTTON_HEIGHT + 10);
    if (GuiButton((Rectangle){ (screenWidth - BUTTON_WIDTH) / 2, saveLoadY, BUTTON_WIDTH, BUTTON_HEIGHT }, "Save Project")) 
    {
        currentPopup = SAVE_PROJECT_POPUP;
    }
    if (GuiButton((Rectangle){ (screenWidth - BUTTON_WIDTH) / 2, saveLoadY + BUTTON_HEIGHT + 10, BUTTON_WIDTH, BUTTON_HEIGHT }, "Load Project")) 
    {
        currentPopup = LOAD_PROJECT_POPUP;
    }
}

void drawLoadProjectPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Load Project", panel.x + 10, panel.y + 10, 20, DARKGRAY);
    DrawText("File Path/Name:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle pathTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(projectFilePathInput, MAX_STR_LEN * 2, &pathEditMode, pathTextbox);

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 130, btnWidth, btnHeight }, "Load")) 
    {
        if (strlen(projectFilePathInput) > 0) 
        {
            loadProject(&head, projectFilePathInput); 
            currentPopup = NO_POPUP;
            projectFilePathInput[0] = '\0';
            pathEditMode = false; 
        } 
        else 
        {
            printf("Error: Enter project file path/name to load!\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 130, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        projectFilePathInput[0] = '\0';
        pathEditMode = false; // Reset edit mode
    }
}

void drawSaveProjectPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing) 
{
    DrawText("Save Project", panel.x + 10, panel.y + 10, 20, DARKGRAY);
    DrawText("Directory Path:", panel.x + 20, panel.y + 50, 18, GRAY);
    Rectangle pathTextbox = { panel.x + 20, panel.y + 75, panel.width - 40, 30 };
    processInput(projectFilePathInput, MAX_STR_LEN * 2, &pathEditMode, pathTextbox);

    DrawText("File Name:", panel.x + 20, panel.y + 115, 18, GRAY);
    Rectangle filenameTextbox = { panel.x + 20, panel.y + 140, panel.width - 40, 30 };
    processInput(projectFileNameInput, MAX_STR_LEN, &filenameEditMode, filenameTextbox);

    if (GuiButton((Rectangle){ panel.x + panel.width/2 - btnWidth - spacing/2, panel.y + 190, btnWidth, btnHeight }, "Save")) 
    {
        if (strlen(projectFilePathInput) > 0 && strlen(projectFileNameInput) > 0) 
        {
            saveProject(&head, projectFilePathInput, projectFileNameInput);
            currentPopup = NO_POPUP;
            projectFilePathInput[0] = '\0';
            projectFileNameInput[0] = '\0';
            pathEditMode = false;     // Reset edit modes
            filenameEditMode = false;
        } 
        else 
        {
            printf("Error: Enter directory path and file name!\n");
        }
    }
    if (GuiButton((Rectangle){ panel.x + panel.width/2 + spacing/2, panel.y + 190, btnWidth, btnHeight }, "Cancel")) 
    {
        currentPopup = NO_POPUP;
        projectFilePathInput[0] = '\0';
        projectFileNameInput[0] = '\0';
        pathEditMode = false;     // Reset edit modes
        filenameEditMode = false;
    }
}