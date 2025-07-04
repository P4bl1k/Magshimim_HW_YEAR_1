#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "View.h"
#include "LinkedList.h"
#include "raygui.h"
#define MAX_STR_LEN 64

extern PopupState currentPopup;
FrameNode* createFrameNode(Frame* frame)
{
    FrameNode* node = (FrameNode*)malloc(sizeof(FrameNode));
    if (!node) return NULL;
    node->frame = frame;
    node->next = NULL;
    return node;
}
void addNewFrame(FrameNode** head, char* framePathInput, char* frameNameInput, int frameDurationInput)
{
    FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
    if (newNode == NULL) 
    {
        printf(":(\n");
        return;
    }
    newNode->frame = (Frame*)malloc(sizeof(Frame));
    if (newNode->frame == NULL) 
    {
        printf("Memory allocation for frame failed.\n");
        free(newNode);
        return;
    }

    strncpy(newNode->frame->path, framePathInput, MAX_STR_LEN - 1);
    newNode->frame->path[MAX_STR_LEN - 1] = '\0';

    strncpy(newNode->frame->name, frameNameInput, MAX_STR_LEN - 1);
    newNode->frame->name[MAX_STR_LEN - 1] = '\0';

    newNode->frame->duration = frameDurationInput;

    newNode->next = *head;
    *head = newNode;

    printf("Frame added successfully!\n");  
}
void removeFrame(FrameNode** head,char* name)
{
    if (head == NULL || *head == NULL) 
    {
        printf("No frames to remove.\n");
        return;
    }

    FrameNode* current = *head;
    FrameNode* previous = NULL;
    
    while (current != NULL && strcmp(current->frame->name, name) != 0) 
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL) 
    {
        printf("Frame not found.\n");
        return;
    }

    if (previous == NULL) 
    {
        *head = current->next; 
    } 
    else 
    {
        previous->next = current->next; 
    }

    free(current->frame);
    free(current);

    printf("Frame removed successfully!\n");
}
bool changeFrameIndex(FrameNode** head,char* frameNameToModify,int newFrameIndexInput) 
{
    if (*head == NULL || newFrameIndexInput < 1) 
    {
        return false;
    }
    Frame* frameToMove = NULL; 
    FrameNode* current = *head;
    FrameNode* newNode = NULL; 
    bool found = false; 
    int i = 1; 
    if (strcmp((*head)->frame->name, frameNameToModify) == 0) 
    {
        frameToMove = (*head)->frame; 
        FrameNode* temp = *head; 
        *head = (*head)->next; 
        free(temp); 
        found = true;
    }
    else 
    {
        while (current->next != NULL && !found) 
        {
            if (strcmp(current->next->frame->name, frameNameToModify) == 0) 
            {
                frameToMove = current->next->frame; 
                FrameNode* temp = current->next; 
                current->next = temp->next;
                free(temp);
                found = true;
            }
            if (!found) 
            {
                current = current->next;
            }
        }
    }
    if (!frameToMove) 
    {
        return false;
    }
    newNode = createFrameNode(frameToMove); 
    if (!newNode) 
    {
        return false;
    }
    if (newFrameIndexInput == 1)
    {
        newNode->next = *head;
        *head = newNode; 
        return true;
    }
    current = *head; 
    for (i = 1; i < newFrameIndexInput - 1 && current->next != NULL; i++)
    {
        current = current->next; 
    }
    newNode->next = current->next; 
    current->next = newNode;
    return true; 
}
void changeFrameDuration(FrameNode** head, char* frameNameToModify, int frameDurationInput)
{
    if (head == NULL || *head == NULL) 
    {
        printf("No frames to change duration.\n");
        return;
    }

    FrameNode* current = *head;

    while (current != NULL && strcmp(current->frame->name, frameNameToModify) != 0) 
    {
        current = current->next;
    }

    if (current == NULL) 
    {
        printf("Frame not found.\n");
        return;
    }

    current->frame->duration = frameDurationInput;

    printf("Frame duration changed successfully!\n");
}
void changeDurationForAll(FrameNode** head, int frameDurationInput)
{
    if (head == NULL || *head == NULL) 
    {
        printf("No frames to change duration for.\n");
        return;
    }

    FrameNode* current = *head;
    while (current != NULL) 
    {
        current->frame->duration = frameDurationInput;
        current = current->next;
    }

    printf("All frame durations changed successfully!\n");
}
void listFrames(FrameNode** head)
{
    if (head == NULL || *head == NULL) 
    {
        printf("No frames to list.\n");
        return;
    }

    FrameNode* current = *head;
    printf("Frames in the list:\n");
    while (current != NULL) 
    {
        printf("Name: %s, Duration: %d, Path: %s\n", current->frame->name, current->frame->duration, current->frame->path);
        current = current->next;
    }
}
void playGIF(FrameNode** head)
{
    if (head == NULL || *head == NULL)
    {
        printf("No frames to play.\n");
        return;
    }
    currentPopup = PLAYBACK_MODE; 
}
void saveProject(FrameNode** head, char* projectFilePathInput, char* projectFileNameInput)
{
    if (head == NULL || *head == NULL) 
    {
        printf("No frames to save.\n");
        return;
    }

    char fullpath[MAX_STR_LEN * 2];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", projectFilePathInput, projectFileNameInput);

    FILE* file = fopen(fullpath, "w");
    if (file == NULL) 
    {
        printf("Could not open file for saving at '%s'.\n", fullpath);
        return;
    }

    FrameNode* current = *head;
    while (current != NULL) 
    {
        fprintf(file, "Name: %s, Duration: %d, Path: %s\n", current->frame->name, current->frame->duration, current->frame->path);
        current = current->next;
    }
    fclose(file);
    printf("Project saved successfully at '%s'!\n", fullpath);
}
void deletelist(FrameNode** head)
{
    if (head == NULL || *head == NULL) 
        return;

    FrameNode* current = *head;
    FrameNode* next;

    while (current != NULL)
    {
        next = current->next;
        free(current->frame);
        free(current);
        current = next;
    }
    *head = NULL;
}
void loadProject(FrameNode** head, char* filename)
{
    if (head == NULL || filename == NULL)
    {
        printf("Invalid parameters for loading project.\n");
        return;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file '%s' for reading.\n", filename);
        return;
    }

    FrameNode* newNode = NULL;
    while (!feof(file))
    {
        newNode = (FrameNode*)malloc(sizeof(FrameNode));
        if (newNode == NULL)
        {
            printf("Memory allocation failed while loading project.\n");
            fclose(file);
            return;
        }
        newNode->frame = (Frame*)malloc(sizeof(Frame));
        if (newNode->frame == NULL)
        {
            printf("Memory allocation for frame failed while loading project.\n");
            free(newNode);
            fclose(file);
            return;
        }

        fscanf(file, "Name: %63[^,], Duration: %d, Path: %63[^\n]\n", newNode->frame->name, &newNode->frame->duration, newNode->frame->path);
        newNode->next = *head;
        *head = newNode;
    }
    fclose(file);
    printf("Project loaded successfully from '%s'!\n", filename);
}