#include "animation_handler.h"

int Lerp(int A, int B, float lerpSpeed, int deltaTime){
    float f_dt = deltaTime * 0.01;

    float interpVal = 1.0 - SDL_pow(lerpSpeed, f_dt);
    float C = A + ((B - A) * interpVal);

    return C; 
}

SDL_Point LerpVect(SDL_Point A, SDL_Point B, float lerpSpeed, int deltatime){
    SDL_Point new;
    new.x = Lerp(A.x, B.x, lerpSpeed, deltatime);
    new.y = Lerp(A.y, B.y, lerpSpeed, deltatime);

    return new;
}