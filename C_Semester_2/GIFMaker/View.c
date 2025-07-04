/**********************************
* Class: MAGSHIMIM Final Project *
* Play function                   *
**********************************/

#include "view.h"
#include <stdio.h>

/**
play the movie!!
display the images each for the duration of the frame one by one and close the window
input: a linked list of frames to display
output: none
**/
void play(FrameNode* list)
{
    if (!list)
    {
        printf("Movie is empty. Nothing to play.\n");
        return;
    }

    FrameNode* head = list;
    int playCount = 0;

    bool windowWasAlreadyOpen = IsWindowReady();

    int screenWidth = 0;
    int screenHeight = 0;

    if (!windowWasAlreadyOpen)
    {
        Image firstImage = LoadImage(head->frame->path);
        if (firstImage.data == NULL)
        {
            printf("Could not load the first image: %s\n", head->frame->path);
            return;
        }
        screenWidth = firstImage.width;
        screenHeight = firstImage.height;
        UnloadImage(firstImage); 

        InitWindow(screenWidth, screenHeight, "GIF Player"); 
        SetTargetFPS(60); 
    }
    else
    {
        Image firstImage = LoadImage(head->frame->path);
        if (firstImage.data == NULL)
        {
            printf("Could not load the first image: %s\n", head->frame->path);
            return;
        }
        screenWidth = firstImage.width;
        screenHeight = firstImage.height;
        UnloadImage(firstImage); 

        if (screenWidth != GetScreenWidth() || screenHeight != GetScreenHeight()) 
        {
            SetWindowSize(screenWidth, screenHeight);
        }
    }
    while (playCount < GIF_REPEAT && !WindowShouldClose()) 
    {
        FrameNode* currentFrameNode = head; 

        while (currentFrameNode != NULL && !WindowShouldClose())
        {
            Image rayImage = LoadImage(currentFrameNode->frame->path);

            if (rayImage.data == NULL)
            {
                printf("Could not open or find image: %s (Frame: %s)\n", currentFrameNode->frame->path, currentFrameNode->frame->name);
                WaitTime((float)currentFrameNode->frame->duration / 1000.0f);
                currentFrameNode = currentFrameNode->next;
                continue;
            }

            Texture2D texture = LoadTextureFromImage(rayImage);
            UnloadImage(rayImage);

            BeginDrawing();
            ClearBackground(BLACK);

            int posX = (GetScreenWidth() - texture.width) / 2;
            int posY = (GetScreenHeight() - texture.height) / 2;
            if (posX < 0) posX = 0;
            if (posY < 0) posY = 0;

            DrawTexture(texture, posX, posY, WHITE); 
            EndDrawing();

            WaitTime((float)currentFrameNode->frame->duration / 1000.0f); 

            UnloadTexture(texture); 

            currentFrameNode = currentFrameNode->next;
        }
        playCount++;
    }
    if (!windowWasAlreadyOpen)
    {
        CloseWindow(); 
    }
}