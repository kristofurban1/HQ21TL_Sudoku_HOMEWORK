#ifndef SudokuInterface_DEF
#define SudokuInterface_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "Cleanup.h"
#include "ErrorHandler.h"
#include "GameState.h"
#include "animation_handler.h"
#include "UI_Elements.h"
#include "Interface.h"
#include "main_menu.h"

#include "Sudoku.h"

extern void SI_Callback_BackButton_Pressed(int sender_UID);

#endif