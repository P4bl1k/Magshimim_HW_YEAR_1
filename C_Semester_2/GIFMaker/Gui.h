#ifndef Gui
#define Gui

#include <stdbool.h>

#define MAX_STR_LEN 64
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 40
#define NUM_MAIN_BUTTONS 7
#define MAX_INPUT_LEN 256


void drawAddFramePopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void drawRemoveFramePopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void drawMoveFramePopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void drawChangeDurationPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void drawChangeAllDurationsPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void drawListFramesDisplay(Rectangle panel, float btnWidth, float btnHeight);
void drawSaveProjectPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void drawLoadProjectPopup(Rectangle panel, float btnWidth, float btnHeight, float spacing);
void processInput(char* buffer, int maxLen, bool* editMode, Rectangle textboxRect);
void drawMainMenu(int screenWidth, int screenHeight, char* title, int fontSize, char *mainButtonText[], int startY);


#endif
