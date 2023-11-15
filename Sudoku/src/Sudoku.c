#include "Sudoku.h"

int SudokuBoardSize = 0;
int Sudoku_BoardDim = 0;
int *SudokuGame = NULL;
int *SudokuSolution = NULL;
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
    int index = 0;

    // Generating a the diagonal of the sudoku board with random numbers, of course respecting the rules of the subgirds(areas).
    // Valid for size 3: 012 345 678 | 123 123 123
    // Invalid example:  012 345 677 | 000 111 222 
    for (int si1 = 0; si1 < SudokuBoardSize; si1++) // si -> seed index 1 / 2
    {
        int candidates[3] = {0,0,0};
        for (int si2 = 0; si2 < SudokuBoardSize; si2++)
        {
            int r = rand();
            int candidate = (r % Sudoku_BoardDim)+1; //0 -- (dim-1) => 1 -- dim

            candidates[si2] = candidate;
        }

        int test = 1;
        while (test < SudokuBoardSize)
        {
            for (int prev = 0; prev < test; prev++)
            {
                if (candidates[prev] == candidates[test]){
                    candidates[test]++;
                    test--;
                    break;
                }
            }
            test++;
        }
        
        for (int si2 = 0; si2 < SudokuBoardSize; si2++)
        {
            int posxy = (si1 * SudokuBoardSize) + si2;
            int index = (posxy * Sudoku_BoardDim) + posxy;
            SudokuSolution[index] = candidates[si2];
        }        
    }
    // Sudoku Seed on diagonal complete.

    // Backtracking with seeds constant.

    

    while (index != Sudoku_BoardDim * Sudoku_BoardDim){
        int row = index / Sudoku_BoardDim;
        int col = index % Sudoku_BoardDim;
        int area = GetAreaFromPos(index);


    }
}

int GetAreaFromPos(int pos){
    int pos_in_row = pos / Sudoku_BoardDim;
    int area_row_index = pos_in_row / SudokuBoardSize;

    int pos_in_col = pos % Sudoku_BoardDim;
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
    int startCol = tmp % Sudoku_BoardDim;
    int startRow = (tmp / Sudoku_BoardDim) * SudokuBoardSize;
    for (int areacellIndex = 0; areacellIndex < Sudoku_BoardDim; areacellIndex++)
    {
        int x = areacellIndex % SudokuBoardSize;
        int y = areacellIndex / SudokuBoardSize;
        int col = startCol + x;
        int row = startRow + y;
        int index = (row * Sudoku_BoardDim) + col;
        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}
bool TestArea(int *board, int areaIndex){
    for (int i = 0; i < Sudoku_BoardDim; i ++){
        if (!TestAreaNum(board, areaIndex, i)) return false;
    }
    return true;
}

void ResetHighlightMap();
void ShowSelectedByUser();
void HighlightNumber(int number);
void ShowErrors();