#ifndef GameState_DEF
#define GameState_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "Cleanup.h"

#define GS_TitleScreen_Durration 2500
extern enum GameStates{
    GS_TitleScreen = 0, 
    GS_MainMenu = 1,
    GS_LeaderBoard = 2,
    GS_Sudoku = 4,
    GS_SudokuEndScreen = 5,
    GS_SudokuConfirmCheat = 6
} GameStates;


#endif