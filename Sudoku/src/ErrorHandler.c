#include "ErrorHandler.h"

extern void malloc_verify(void *ptr){
    if (ptr == NULL) { error_message = MSG_MALLOC_ERROR; }
}

extern void SDL_ptr_verify(void *ptr){
    
    if (ptr == NULL) {strcpy(error_message, SDL_GetError());}
}

extern void SDL_verify(int err_c){
    if (err_c < 0) { strcpy(error_message, SDL_GetError());}//*error_message = SDL_GetError(); }
}

static void RAISE_ERROR(){
    if (GarbageCollector != NULL) EXECUTE_CLEANUP();
    exit(1);
}