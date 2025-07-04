#ifndef LinkedList
#define LinkedList
#define MAX_STR_LEN 64

typedef struct Frame
{
	char name[MAX_STR_LEN];
	int duration;
	char path[MAX_STR_LEN];
} Frame;

typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

void addNewFrame(FrameNode** head, char* framePathInput, char* frameNameInput, int frameDurationInput);
void removeFrame(FrameNode** head,char* name);	
bool changeFrameIndex(FrameNode** head,char* frameNameToModify,int newFrameIndexInput);
void changeFrameDuration(FrameNode** head,char* frameNameToModify,int frameDurationInput);
void changeDurationForAll(FrameNode** head,int frameDurationInput);
void listFrames(FrameNode** head);
void playGIF(FrameNode** head);
void saveProject(FrameNode** head, char* projectFilePathInput, char* projectFileNameInput);
void loadProject(FrameNode** head, char* filename);
void deletelist(FrameNode** head);
#endif