#ifndef ERROR_HANDLER_DEF
#define ERROR_HANDLER_DEF

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Cleanup.h"

#include <SDL2/SDL.h>

#define MSG_MALLOC_ERROR "Error: Malloc failed!"

static char *error_message;
extern char *error_identifier;

/*
    @brief Verifies if malloc if succesful. Raises error if it fails.
*/
extern void malloc_verify(void *ptr);

/*
    @brief Verifies SDL NULL pointer exceptions.
*/
extern void SDL_ptr_verify(void *ptr);

/*
    @brief Verifies that SDL command executed succesfully. Raises error if it falis.
*/
extern void SDL_verify(int err_c);

/*
    @brief When encountering fatal error, this will immidietly clean up and exit.
*/
static void RAISE_ERROR();

#endif