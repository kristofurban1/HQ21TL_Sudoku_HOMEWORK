#include "main.h"

extern int main(int argc, char *argv[]) {
    
    MainWindowWidth  = Default_WIDTH;
    MainWindowHeight = Default_HEIGHT;

    GC_Init();          // GarbageCollector
    INITIALIZE_ALL();   // SDL
    
    SDL_SetRenderDrawColor(MainRenderer, 0, 255, 255, 255);
    SDL_RenderClear(MainRenderer);

    bool render = true;
    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        if (render){
            SDL_RenderPresent(MainRenderer);

            SDL_SetRenderDrawColor(MainRenderer, 0, 255, 255, 255);
            SDL_RenderClear(MainRenderer);
            render = false;
        }
    }

    EXECUTE_CLEANUP();

    return 0;
}
