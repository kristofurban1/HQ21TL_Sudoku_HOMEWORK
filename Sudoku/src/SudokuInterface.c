#include "SudokuInterface.h"

void SI_Callback_BackButton_Pressed(int sender_UID){
    printf("SI: BACKBUTTON_PRESSED\n");
    SetGameState(GS_MainMenu);
    SetSudokuState(GS_UNSET);

    UIElements_Generate();
    Interface_InitCurrentState();
}