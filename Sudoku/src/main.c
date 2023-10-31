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

    SDL_SetWindowTitle(MainWindow, WINDOW_TITLE);
    SDL_Surface *icon = IMG_Load(GetAsset(ASSET_ICON));
    SDL_SetWindowIcon(MainWindow, icon);
    SDL_FreeSurface(icon);

    UIElements_GenerateStatic();

    uint8_t gamestate = GS_TitleScreen;
    uint8_t gamestate_sudoku = GS_UNSET;

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
                        bool changed = false;
                        if (MainWindowWidth >= Minimum_Width)
                            MainWindowWidth  = event.window.data1;
                        else { MainWindowWidth = Minimum_Width; changed = true; }
                        
                        if (MainWindowHeight >= Minimum_Heigth)
                            MainWindowHeight = event.window.data2;
                        else { MainWindowHeight = Minimum_Heigth; changed = true; }

                        if (changed) SDL_SetWindowSize(MainWindow, MainWindowWidth, MainWindowHeight);

                        render = true;
                        UIElements_GenerateStatic();
                    }

                    break;
                default:
                    break;
            }
        }
        if (timer_forceRender + FPS < SDL_GetTicks64()){
            timer_forceRender = SDL_GetTicks64();

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

                break;
            
            case GS_MainMenu:
                Render_TextureElement(Title);
                break;
            case GS_SudokuState:
                switch (gamestate_sudoku)
                    {
                    case GS_Sudoku:
                        /* code */
                        break;
                    case GS_SudokuEndScreen:
                        break;
                    case GS_SudokuConfirmCheat:
                        break;
                    
                    default:
                        SetErrorMessage("Unknown gamestate_sudoku"); SetErrorIndentfyer("main: SudokuState control");
                        RAISE_ERROR();
                        break;
                }
                break;
            
            default:
                SetErrorMessage("Unknown gamestate"); SetErrorIndentfyer("main: GameState control");
                RAISE_ERROR();
                break;
            }
            #pragma endregion

            render = true;
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
