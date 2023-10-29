/*
    File Handler


*/

#ifndef FILEHANDLER_DEF
#define FILEHANDLER_DEF


#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "datastructures.h"

#define PATH_SAVADATA       "data\\savedata.bin"
#define PATH_LEADERBOARD    "data\\leaderboard.bin"

#define PATH_ASSETS     "data\\assets\\"
extern char *BasePath;

static bool FileExists(const char *filename);

static char *AppendToBasePath(char *endOfPath, char *basePath);

extern void FileHandler_Init();

extern struct SaveData *ReadSaveData();

extern bool WriteSaveData(struct SaveData *data);

extern struct Leaderboard_Entry *ReadLEaderboard();

extern bool WriteLeaderboard(struct Leaderboard_Entry *entry);


#endif