#ifndef Interface_DEF
#define Interface_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "Cleanup.h"
#include "ErrorHandler.h"
#include "GameState.h"
#include "animation_handler.h"
#include "UI_Elements.h"

#include "main_menu.h"
#include "SudokuInterface.h"

#include <SDL2/SDL.h>

extern int CurrentTriggerAreaID;

extern void Interface_InitCurrentState();

extern void Interface_EventHandler_Keyboard(SDL_Scancode keypress);
extern void Interface_EventHandler_Mouse(SDL_Point cursorClick);

#endif