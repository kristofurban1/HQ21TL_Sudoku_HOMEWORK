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
        // Elements in sudoku cell elements are appended to render pipeline. S
        // Since pipline has generating and freeing priority, this list's elements will be freed before this function executes. 
        //      (When redrawig window after window size changed for example.)

    struct UI_Element *panel = UI_GetByID(SUDOKUPANEL_UID);
    int cellCount = GetBoardTotalSize();
    int numOfCellsInRow = GetBoardDimensions();

    sudokuCellElements = malloc(sizeof(struct UI_Element *) * cellCount);
        malloc_verify(sudokuCellElements);


    int borderWidth = panel->pos.width * 0.1;
    int CellSizeWithBorder = (panel->pos.width / numOfCellsInRow) - borderWidth; // Width == Height in panel and cell. ; -borderWidht => every cell has one (side) border except last cell.
    int cellSize = CellSizeWithBorder - borderWidth;

    #pragma region sudokuBackgroundGrid
    struct UI_Element *sudokuBackground = malloc(sizeof(sudokuBackground));
        malloc_verify(sudokuBackground);

        sudokuBackground->UniqueID = -1;
        sudokuBackground->visible = true;
        sudokuBackground->hasAnim = false;
        sudokuBackground->hasLabel = false;
        sudokuBackground->hasTrigger = false;
        sudokuBackground->hasBackground = true;

        
    #pragma endregion


    #pragma region CellBackground_shape
    struct Shape *cellbg_shape = malloc(sizeof(struct Shape)); malloc_verify(cellbg_shape);

        cellbg_shape->height = cellSize * 0.9;
        cellbg_shape->width  = cellSize * 0.9;
        cellbg_shape->offset_X = cellSize * 0.1;
        cellbg_shape->offset_Y = cellSize * 0.1;

        cellbg_shape->boundrary_start = malloc(sizeof(int) * cellbg_shape->height);
        cellbg_shape->boundrary_end   = malloc(sizeof(int) * cellbg_shape->height);

        for (int i = 0; i < 90; i++)
        {
            float rad = i * (M_PI / 180);
            float radius = cellbg_shape->height / 2;
            int y = radius * sin(rad);
            int x = radius * (1 - cos(rad));

            cellbg_shape->boundrary_start[(int)(radius - y)] = x;
            cellbg_shape->boundrary_start[(int)(radius + y)] = x;

            cellbg_shape->boundrary_end[(int)(radius - y)] = cellbg_shape->width - x;
            cellbg_shape->boundrary_end[(int)(radius + y)] = cellbg_shape->width - x;
        }
    
    for (int cell_iter = 0; cell_iter < cellCount; cell_iter++)
    {
        
    }
    


        
    #pragma endregion

}

void SI_GenerateSudoku(){
    int boardsize = GetBoardSize();
    

    GenerateBoard(boardsize);
}

