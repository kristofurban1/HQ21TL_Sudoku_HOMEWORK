#ifndef Sudoku_DEF
#define Sudoku_DEF

#include <stdbool.h>
#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "Cleanup.h"
#include "backtracking.h"

#define DifficultyEasy      0.8
#define DifficultyMedium    0.6
#define DifficultyHard      0.4
#define DifficultyExtreme   0.2

extern int SudokuBoardSize;
extern int Sudoku_BoardDim;
extern int *SudokuGame;
extern int *SudokuSolution;
extern int *HighlightMap; // 0: normal; 1: Selected by user; 2: Highlighted; 4: Error
extern int SelectedByUser;

extern bool HighlightEnabled;
extern int GameAvailableHelp;
extern bool AutoHelp;

extern int GetBoardTotalSize();
extern int GetBoardDimensions();

extern void GenerateBoard(int boardsize);
extern void SolveGame();

extern int GetAreaFromPos(int pos);

extern bool TestRowNum(int *board, int rowIndex, int num);
extern bool TestRow(int *board, int rowIndex);
extern bool TestColNum(int *board, int colIndex, int num);
extern bool TestCol(int *board, int colIndex);
extern bool TestAreaNum(int *board, int areaIndex, int num);
extern bool TestArea(int *board, int areaIndex);

extern void ResetHighlightMap();
extern void ShowSelectedByUser();
extern void HighlightNumber(int number);
extern void ShowErrors();





#endif