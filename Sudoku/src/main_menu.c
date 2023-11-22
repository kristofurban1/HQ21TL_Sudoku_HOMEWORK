#include "main_menu.h"

void MM_Callback_StartButton_Pressed(int sender_uid){
    printf("MM: STARTBUTTON_PRESSED\n");
    SetGameState(GS_SudokuState);
    SetSudokuState(GS_Sudoku);
    SI_GenerateSudoku();
    UIElements_Generate();
    GenerateSudokuCellElements();
    Interface_InitCurrentState();
}

extern void SetBoardSize(int newsize) { BoardSize = newsize; }
extern int GetBoardSize() { return BoardSize; }