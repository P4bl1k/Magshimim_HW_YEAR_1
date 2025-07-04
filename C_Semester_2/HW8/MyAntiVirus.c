#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dirent.h"

//Defines

#define FALSE 0
#define TRUE !FALSE

#define DIRECTORY_D_TYPE 16384

#define FOLDER_PARAM 1
#define SIGNATURE_PARAM 2

#define INFECTED_FIRST_20_PERCENT 3
#define INFECTED_LAST_20_PERCENT 2
#define INFECTED 1
#define NOT_INFECTED 0
#define READING_ERROR -1

#define NORMAL_SCAN_MODE 1
#define QUICK_SCAN_MODE 2
#define BEG_FILE_PERCENT 0.2
#define END_FILE_PERCENT 0.8

#define LOG_FILE_NAME "AntiVirusLog.txt"
#define BACKSLASH "/"


char* logPath = NULL;

//Declarations

int showMenu(void);
int scanFile(char*, char*, int);
int searchSignature(FILE*, FILE*, double, double);
int getFileSize(FILE*);

char** getFileNames(char*, int*);
void alphabetizeNames(char**, int);

void openLog(char*);
char* createLogPath(char*);
void updateLogMessage(char*);
void updateLogScanResult(char*, int);
char* getResultString(int);

//Main Function

int main(int argc, char** argv)
{
	int i = 0, numFiles = 0;
	int infected = 0, filesScanned = 0, result = 0;
	int decision = 0;

	char** fileNames = getFileNames(argv[FOLDER_PARAM], &numFiles);
	alphabetizeNames(fileNames, numFiles);

	openLog(argv[FOLDER_PARAM]);
	updateLogMessage("Anti-virus began! Welcome!\n");
	updateLogMessage("Folder to scan: ");
	updateLogMessage(argv[FOLDER_PARAM]);
	updateLogMessage("Virus signature: ");
	updateLogMessage(argv[SIGNATURE_PARAM]);

	printf("Welcome to my Virus Scan!\n\n");
	printf("Folder to scan: %s\n", argv[FOLDER_PARAM]);
	printf("Virus signature: %s\n\n", argv[SIGNATURE_PARAM]);
	decision = showMenu();

	printf("Scanning began...\nThis process may take several minutes...\n\n");
	printf("Scanning:\n");
	updateLogMessage("Results:");

	for (i = 0; i < numFiles; i++)
	{
		infected = NOT_INFECTED;
		printf("%s - ", fileNames[i]);
		result = scanFile(fileNames[i], argv[SIGNATURE_PARAM], decision ? QUICK_SCAN_MODE : NORMAL_SCAN_MODE);
		printf("%s\n", getResultString(result));
		filesScanned++;
		updateLogScanResult(fileNames[i], result);
	}

	printf("Scan Completed.\n");
	printf("See log path for results: ");
	printf("%s\n", logPath);

	for (i = 0; i < numFiles; i++)
		free(fileNames[i]);
	free(fileNames);
	free(logPath);

	getchar();
	return 0;
}

//Functions

int showMenu(void)
{
	int choice = 0;
	printf("Press 0 for a normal scan or any other key for a quick scan: ");
	scanf("%d", &choice);
	getchar();

	updateLogMessage("\nScanning option:");
    if(choice)
    {
        updateLogMessage("Quick Scan\n");
    }
    else
    {
		updateLogMessage("Normal Scan\n");
    }
	return choice;
}

int scanFile(char* sourcePath, char* signPath, int mode)
{
	int result = NOT_INFECTED;
	FILE* source = fopen(sourcePath, "rb");
	FILE* sign = fopen(signPath, "rb");

	if (!source || !sign)
	{
		printf("Error opening file\n");
		return READING_ERROR;
	}

	if (mode == QUICK_SCAN_MODE)
	{
		if (searchSignature(source, sign, 0.0, BEG_FILE_PERCENT))
		{
			result = INFECTED_FIRST_20_PERCENT;
		}
		else if (searchSignature(source, sign, END_FILE_PERCENT, 1.0))
		{
			result = INFECTED_LAST_20_PERCENT;
		}
		else
		{
			double ratio = (double)getFileSize(sign) / getFileSize(source);
			double newBeg = BEG_FILE_PERCENT - ratio;
			if (newBeg < 0) newBeg = 0.0;

			double newEnd = END_FILE_PERCENT + ratio;
			if (newEnd > 1) newEnd = 1.0;

			if (searchSignature(source, sign, newBeg, newEnd))
			{
				result = INFECTED;
			}
		}
	}
	else
	{
		if (searchSignature(source, sign, 0.0, 1.0))
		{
			result = INFECTED;
		}
	}

	fclose(source);
	fclose(sign);
	return result;
}

int searchSignature(FILE* file, FILE* sign, double beg, double end)
{
	int found = FALSE;
	int fileCh = 0
    int signCh = 0;

	int signSize = getFileSize(sign);
	int fileSize = getFileSize(file);

	int startBit = (int)(fileSize * beg);
	int endBit = (int)(fileSize * end);
	int currFileLocation = startBit;

	while (currFileLocation <= endBit - signSize && !found)
	{
		fseek(file, currFileLocation, SEEK_SET);
		currFileLocation++;
		fseek(sign, 0, SEEK_SET);
		found = TRUE;

		while ((signCh = fgetc(sign)) != EOF)
		{
			fileCh = fgetc(file);
			if (fileCh != signCh)
			{
				found = FALSE;
				break;
			}
		}
	}
	return found;
}

char** getFileNames(char* dirPath, int* size)
{
	DIR* d = 0;
	struct dirent* dir = 0;
	int numOfFiles = 0, fileNameLength = 0;
	int pathLen = strlen(dirPath);
	char** names = (char**)malloc(sizeof(char*));

	if (!names) return NULL;

	d = opendir(dirPath);
	if (!d) 
    {
        return NULL;
    }
	while ((dir = readdir(d)) != NULL)
	{
		if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..") && dir->d_type != DIRECTORY_D_TYPE)
		{
			numOfFiles++;
			names = (char**)realloc(names, sizeof(char*) * numOfFiles);
			fileNameLength = strlen(dir->d_name);
			names[numOfFiles - 1] = (char*)calloc(pathLen + fileNameLength + 2, sizeof(char));
			strncpy(names[numOfFiles - 1], dirPath, pathLen);
			strncat(names[numOfFiles - 1], BACKSLASH, 1);
			strncat(names[numOfFiles - 1], dir->d_name, fileNameLength);
		}
	}
	*size = numOfFiles;
	closedir(d);
	return names;
}

void alphabetizeNames(char** fileNames, int numFiles)
{
	int i = 0, j = 0;
	char* temp = 0;

	for (i = 0; i < numFiles; i++)
	{
		for (j = 0; j < numFiles - 1; j++)
		{
			if (strcmp(fileNames[j], fileNames[i]) > 0)
			{
				temp = fileNames[i];
				fileNames[i] = fileNames[j];
				fileNames[j] = temp;
			}
		}
	}
}
void openLog(char* path)
{
	logPath = createLogPath(path);
	FILE* logFile = fopen(logPath, "wb");
	fclose(logFile);
}

char* createLogPath(char* path)
{
	unsigned int pathLen = strlen(path);
	unsigned int logLen = strlen(LOG_FILE_NAME);
	char* logPath = (char*)calloc((pathLen + logLen + 2), sizeof(char));
	strncpy(logPath, path, pathLen);
	strncat(logPath, BACKSLASH, 1);
	strncat(logPath, LOG_FILE_NAME, logLen);
	return logPath;
}

void updateLogScanResult(char* fileName, int result)
{
	FILE* file = fopen(logPath, "ab");
	if (file)
	{
		fputs(fileName, file);
		fprintf(file, "  %s\r\n", getResultString(result));
		fclose(file);
	}
}

char* getResultString(int result)
{
	char* resultString = 0;
	switch (result)
	{
		case INFECTED_FIRST_20_PERCENT:
			resultString = "Infected! (first 20%)";
			break;
		case INFECTED_LAST_20_PERCENT:
			resultString = "Infected! (last 20%)";
			break;
		case INFECTED:
			resultString = "Infected!";
			break;
		case NOT_INFECTED:
			resultString = "Clean";
			break;
		case READING_ERROR:
			resultString = "Reading Error";
			break;
		default:
			resultString = "Unknown Result, please contact customer support";
			break;
	}
	return resultString;
}

void updateLogMessage(char* msg)
{
	FILE* file = fopen(logPath, "ab");
	if (file)
	{
		fprintf(file, "%s\r\n", msg);
		fclose(file);
	}
}

int getFileSize(FILE* f)
{
	fseek(f, 0, SEEK_SET);
	int ch = 0, size = 0;
	while ((ch = fgetc(f)) != EOF)
    {
		size++;
    }
	rewind(f);
	return size;
}
