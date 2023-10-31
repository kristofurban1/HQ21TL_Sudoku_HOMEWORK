#ifndef GameState_DEF
#define GameState_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "Cleanup.h"

#define GS_TitleScreen_Durration 2500

#define GS_SudokuMask 0b0100

extern enum GameStates{
    GS_TitleScreen = 0, 
    GS_MainMenu = 1,
    GS_LeaderBoard = 2,
    GS_SudokuState = 3,
} GameStates;

extern enum SudokuState{
    GS_Sudoku = 0,
    GS_SudokuEndScreen = 1,
    GS_SudokuConfirmCheat = 2,
    GS_UNSET = 3
} SudokuState;


#endif