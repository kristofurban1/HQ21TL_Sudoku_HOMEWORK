#ifndef MAIN_DEF
#define MAIN_DEF

#include "debugmalloc.h"

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "Cleanup.h"
#include "Init.h"

/*
    Program Main entry point.
    Accepts default argument, these will be ignored.
*/
extern int main(int argc, char *argv[]);

#endif