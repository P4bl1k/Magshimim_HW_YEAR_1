/*********************************
* Class: MAGSHIMIM Final Project *
* Play function declaration          *
**********************************/

#ifndef VIEWH
#define VIEWH

#include "raylib.h"
#include "LinkedList.h" 

typedef enum {
    NO_POPUP,
    ADD_FRAME_POPUP,
    REMOVE_FRAME_POPUP,
    CHANGE_DURATION_POPUP,
    CHANGE_ALL_DURATIONS_POPUP,
    MOVE_FRAME_POPUP,
    SAVE_PROJECT_POPUP,
    LOAD_PROJECT_POPUP,
    LIST_FRAMES_DISPLAY,
    PLAYBACK_MODE
} PopupState;

#define GIF_REPEAT 5

void play(FrameNode* list);

#endif

