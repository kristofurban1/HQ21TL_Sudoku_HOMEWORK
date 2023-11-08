#ifndef anim_handler_DEF
#define anim_handler_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "Cleanup.h"

#include <SDL2/SDL.h>

extern int Lerp(int A, int B, float lerpSpeed, int deltaTime);
extern SDL_Point LerpVect(SDL_Point A, SDL_Point B, float lerpSpeed, int deltatime);

extern struct Animation{
    SDL_Point targetPos;
    float fspeed;
} Animation;


#endif