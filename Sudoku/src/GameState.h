#ifndef GameState_DEF
#define GameState_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "Cleanup.h"

#define GS_TitleScreen_Durration 2000

static int current_GameState;
static int current_SudokuState;

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

extern void Gamestate_Init();

extern int GetGamestate();
extern void SetGameState(int newState);
extern int GetSudokustate();
extern void SetSudokuState(int newState);



#endif