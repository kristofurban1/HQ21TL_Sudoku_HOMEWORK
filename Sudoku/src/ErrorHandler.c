#include "ErrorHandler.h"

extern void malloc_verfy(void *ptr){
    if (ptr == NULL) { error_message = MSG_MALLOC_ERROR; }
}

extern void SDL_ptr_verfy(void *ptr){
    if (ptr == NULL) {error_message = SDL_GetError(); }
}

extern void SDL_verify(int err_c){
    if (err_c < 0) { error_message = SDL_GetError(); }
}

static void RAISE_ERROR(){
    if (GarbageCollector != NULL) EXECUTE_CLEANUP();
    exit();
}