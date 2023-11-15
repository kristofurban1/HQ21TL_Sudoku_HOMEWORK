#ifndef MAIN_MENU_DEF
#define MAIN_MENU_DEF

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

static int BoardSize;
extern void SetBoardSize(int newsize);
extern int GetBoardSize();

extern void MM_Callback_StartButton_Pressed(int sender_uid);

#endif