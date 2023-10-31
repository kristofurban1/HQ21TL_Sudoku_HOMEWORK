#ifndef ERROR_HANDLER_DEF
#define ERROR_HANDLER_DEF

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "debugmalloc.h"

#define MSG_MALLOC_ERROR "Error: Malloc failed!"

static char *error_message;
static char *error_identifyer;

/*
    @brief Sets the error identifyer variable.
*/
extern void SetErrorIndentfyer(char *errid);

/*
    @brief Sets the error message variable.
*/
extern void SetErrorMessage(char *errmsg);

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
    @brief When encountering fatal error, this will print the error message and identifyer then exit without cleanup.
*/
extern void RAISE_ERROR();

#endif