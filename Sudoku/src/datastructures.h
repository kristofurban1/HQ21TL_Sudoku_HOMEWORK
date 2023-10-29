#ifndef DATASTRUCT_DEF
#define DATASTRUCT_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned short uint_16;

extern enum game_Difficulty { 
    game_dif_EASY       = 0, 
    game_dif_MEDIUM     = 1, 
    game_dif_HARD       = 2, 
    game_dif_EXTREME    = 3 
} game_Difficulty;

extern enum game_CheatLevel { 
    game_chlvl_NONE             = (uint_16)0, 
    game_chlvl_HIGHLIGHT        = (uint_16)1, 
    game_chlvl_ERROR_LIMITED    = (uint_16)2, 
    game_chlvl_ERROR_UNLIMITED  = (uint_16)4, 
    game_chlvl_ERROR_AUTO       = (uint_16)6
} game_CheatLevel;

extern struct Leaderboard_Entry {
    int u16BoardSize;
    uint_16 u16Difficulty;
    uint_16 u16CheatLevel;
    long int Seconds;
} Leaderboard_Entry;

extern struct SaveData {
    int u16BoardSize;
    uint_16 u16Difficulty;
    uint_16 u16CheatLevel;
    int WindowWidth, WindowHeight;
} SaveData;

#endif