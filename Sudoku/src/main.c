#include "main.h"

int MainWindowWidth  = Default_WIDTH;
int MainWindowHeight = Default_HEIGHT;
SDL_Window *MainWindow      = NULL;
SDL_Renderer *MainRenderer  = NULL;

extern int main(int argc, char *argv[]) {
    GC_Init();          // GarbageCollector
    INITIALIZE_ALL();   // SDL
    FileHandler_Init(); // FileHandler
    FontManager_Init(); // FontManager
    UIElements_Init();  //UI_Elements

    SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 255);
    SDL_RenderClear(MainRenderer);
    SDL_RenderPresent(MainRenderer);

    UIElements_GenerateStatic();

    uint8_t gamestate = GS_TitleScreen;

    Uint64 timer_forceRender = SDL_GetTicks64();
    Uint64 gamestate_timer = 0;

    bool render = true;
    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        MainWindowWidth  = event.window.data1;
                        MainWindowHeight = event.window.data2;
                        UIElements_GenerateStatic();
                        render = true;
                    }

                    break;
                default:
                    break;
            }
        }
        if (timer_forceRender + FPS < SDL_GetTicks64()){
            timer_forceRender = SDL_GetTicks64();
            render = true;

            SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
            SDL_RenderClear(MainRenderer);

            #pragma region DrawScreen
            switch (gamestate)
            {
            case GS_TitleScreen:
                if (gamestate_timer == 0) gamestate_timer = SDL_GetTicks64() + GS_TitleScreen_Durration;
                if (gamestate_timer < SDL_GetTicks64()) {gamestate = GS_MainMenu; gamestate_timer = 0; break; }

                SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 255);
                SDL_RenderClear(MainRenderer);
                Render_TextureElement(TitleScreen);
                SDL_RenderPresent(MainRenderer);

                break;
            
            default:
                SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
                SDL_RenderClear(MainRenderer);
                break;
            }
            #pragma endregion
        }
        if (render){
            SDL_RenderPresent(MainRenderer);
            render = false;
        }
        SDL_Delay(1);
    }

    EXECUTE_CLEANUP();
    TTF_CloseFont(GetFont());
    SDL_Quit();

    return 0;
}
