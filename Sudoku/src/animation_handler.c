#include "animation_handler.h"

int Lerp(int A, int B, float lerpSpeed, int deltaTime){
    float f_interval = (lerpSpeed * deltaTime);
    return A + ((B-A) / f_interval); 
}

SDL_Point LerpVect(SDL_Point A, SDL_Point B, float lerpSpeed, int deltatime){
    SDL_Point new;
    new.x = Lerp(A.x, B.x, lerpSpeed, deltatime);
    new.y = Lerp(A.y, B.y, lerpSpeed, deltatime);

    return new;
}