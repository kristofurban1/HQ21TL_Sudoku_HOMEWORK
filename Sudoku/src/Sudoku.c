#include "Sudoku.h"

int SudokuBoardSize = 0;
int Sudoku_BoardDim = 0;
int *SudokuGame = NULL;
int SudokuSolution = NULL;
int *HighlightMap = NULL; // 0: normal; 1: Selected by user; 2: Highlighted; 4: Error
int SelectedByUser = -1;

bool HighlightEnabled = false;
int GameAvailableHelp = 0;
bool AutoHelp = false;

void GenerateBoard(int boardsize){
    if (Sudoku_BoardDim != 0) TryFree(SudokuGame);

    SudokuBoardSize = boardsize;
    Sudoku_BoardDim = boardsize * boardsize;

    int allocationSize = sizeof(int) * Sudoku_BoardDim * Sudoku_BoardDim;

    SudokuGame = malloc(allocationSize);
        malloc_verify(SudokuGame);
    memset(SudokuGame, 0, allocationSize);

    SudokuSolution = malloc(allocationSize);
        malloc_verify(SudokuSolution);
    memset(SudokuSolution, 0, allocationSize);

    HighlightMap = malloc(allocationSize);
        malloc_verify(HighlightMap);
    memset(HighlightMap, 0, allocationSize);
}

void SolveGame(){
    int targetMax = Sudoku_BoardDim;

    for (int i = 0; i < Sudoku_BoardDim * Sudoku_BoardDim; i++)
    {
        int row = i / Sudoku_BoardDim;
        int col = i % Sudoku_BoardDim;
        int area = GetAreaFromPos(i);

         
    }
    
}

int GetAreaFromPos(int pos){
    int pos_in_row = pos % Sudoku_BoardDim;
    int area_row_index = pos_in_row / SudokuBoardSize;

    int pos_in_col = pos / Sudoku_BoardDim;
    int area_col_index = pos_in_col / SudokuBoardSize;

    int areaIndex = (area_row_index * SudokuBoardSize) + area_col_index;

    return areaIndex;
}

bool TestRowNum(int *board, int rowIndex, int num){
    bool found = false;
    for (int col = 0; col < Sudoku_BoardDim; col++)
    {
        int index = (rowIndex * Sudoku_BoardDim) + col;
        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}
bool TestRow(int *board, int rowIndex){
    for (size_t i = 1; i <= Sudoku_BoardDim; i++)
        if (!TestRowNum(board, rowIndex, i)) return false;
    return true;
}

bool TestColNum(int *board, int colIndex, int num){
    bool found = false;
    for (int row = 0; row < Sudoku_BoardDim; row++)
    {
        int index = (row * Sudoku_BoardDim) + colIndex; 
        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}
bool TestCol(int *board, int colIndex){
    for (size_t i = 1; i <= Sudoku_BoardDim; i++)
        if (!TestColNum(board, colIndex, i)) return false;
    return true;
}

bool TestAreaNum(int *board, int areaIndex, int num){
    bool found = false;
    int tmp = areaIndex * SudokuBoardSize;
    int startRow = tmp / Sudoku_BoardDim;
    int startCol = 
    for (int areacellIndex = 0; areacellIndex < Sudoku_BoardDim; areacellIndex++)
    {

        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}
bool TestArea(int *board, int areaIndex);

void ResetHighlightMap();
void ShowSelectedByUser();
void HighlightNumber(int number);
void ShowErrors();