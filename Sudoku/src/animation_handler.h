#ifndef anim_handler_DEF
#define anim_handler_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "Cleanup.h"

#include <SDL2/SDL.h>

int Lerp(int A, int B, float lerpSpeed, int deltaTime);

SDL_Point LerpVect(SDL_Point A, SDL_Point B, float lerpSpeed, int deltatime);

#endif