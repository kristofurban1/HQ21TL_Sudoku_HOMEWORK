#include "main.h"

int MainWindowWidth  = Default_WIDTH;
int MainWindowHeight = Default_HEIGHT;
SDL_Window *MainWindow      = NULL;
SDL_Renderer *MainRenderer  = NULL;

extern int main(int argc, char *argv[]) {
    GC_Init();          // GarbageCollector
    INITIALIZE_ALL();   // SDL

    FileHandler_Init();
    
    SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
    SDL_RenderClear(MainRenderer);

    Uint64 timer_forceRender = SDL_GetTicks64();

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



        if (timer_forceRender + FPS < SDL_GetTicks64()){
            timer_forceRender = SDL_GetTicks64();
            render = true;
        }
        if (render){
            SDL_RenderPresent(MainRenderer);

            SDL_SetRenderDrawColor(MainRenderer, 0, 255, 255, 255);
            SDL_RenderClear(MainRenderer);
            render = false;
        }
        SDL_Delay(1);
    }

    EXECUTE_CLEANUP();
    SDL_Quit();

    return 0;
}
