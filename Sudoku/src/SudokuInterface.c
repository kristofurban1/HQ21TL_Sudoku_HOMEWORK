#include "SudokuInterface.h"

struct UI_Element **sudokuCellElements = NULL;

void SI_Callback_BackButton_Pressed(int sender_UID){
    printf("SI: BACKBUTTON_PRESSED\n");
    SetGameState(GS_MainMenu);
    SetSudokuState(GS_UNSET);

    UIElements_Generate();
    Interface_InitCurrentState();
}

void GenerateSudokuCellElements(){
    TryFree(sudokuCellElements);

    int cellCount = GetBoardTotalSize();

    #pragma region CellBackground_shape
    struct Shape *cellbg_shape = malloc(sizeof(struct Shape)); malloc_verify(cellbg_shape);

        //cellbg_shape->height = 
        
    #pragma endregion

}

void SI_GenerateSudoku(){
    int boardsize = GetBoardSize();
    

    GenerateBoard(boardsize);
}

