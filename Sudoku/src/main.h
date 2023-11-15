#ifndef MAIN_DEF
#define MAIN_DEF

#include "debugmalloc.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "Cleanup.h"
#include "Init.h"
#include "file_handler.h"
#include "animation_handler.h"
#include "GameState.h"
#include "UI_Elements.h"
#include "UI_Renderer.h"
#include "Interface.h"

/*
    Program Main entry point.
    Accepts default arguments, these will be ignored.
*/
extern int main(int argc, char *argv[]);

#endif