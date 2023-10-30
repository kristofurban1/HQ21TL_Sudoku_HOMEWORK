/*
    File Handler


*/

#ifndef FILEHANDLER_DEF
#define FILEHANDLER_DEF


#include <stdio.h>
#include <stdbool.h>
#include <io.h>

#include <SDL2/SDL.h>

#include "datastructures.h"
#include "WINDOW_PARAMETERS.h"

#include "Cleanup.h"

#define PATH_SAVEDATA       "data\\savedata.bin"
#define PATH_LEADERBOARD    "data\\leaderboard.bin"

#define DIR_DATA           "data\\"
#define DIR_ASSETS          "data\\assets\\"

static bool FileExists(const char *filename);

static char *AppendToBasePath(char *endOfPath, char *basePath);

extern void FileHandler_Init();

extern struct SaveData *GetDefaultSaveData();

extern struct SaveData *ReadSaveData();

extern void WriteSaveData(struct SaveData *data);

extern struct Leaderboard_Entry *ReadLEaderboard();

extern void WriteLeaderboard(struct Leaderboard_Entry *entry);


#endif