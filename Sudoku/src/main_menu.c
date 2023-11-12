#include "main_menu.h"

void MM_Callback_StartButton_Pressed(int sender_uid){
    printf("MM: STARTBUTTON_PRESSED\n");
    SetGameState(GS_SudokuState);
    SetSudokuState(GS_Sudoku);
    UIElements_Generate();
    Interface_InitCurrentState();
}