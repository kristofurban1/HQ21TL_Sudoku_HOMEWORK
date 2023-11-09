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
    ResetElements();  // UI_Elements
    Gamestate_Init();   // Gamestate

    SDL_SetWindowTitle(MainWindow, WINDOW_TITLE);
    SDL_Surface *icon = IMG_Load(GetAsset(ASSET_ICON));
    SDL_SetWindowIcon(MainWindow, icon);
    SDL_FreeSurface(icon);

    UIElements_Generate();


    Uint64 timer_forceRender = SDL_GetTicks64();
    Uint64 gamestate_timer = 0;

    SDL_Point p;
    p.x = 100;
    p.y = 100;

    SDL_Point target;
    target.x = 100;
    target.y = 100;

    bool running = true;
    Uint64 deltaTime = 0;
    Uint64 deltaPrev = SDL_GetTicks64();
    while(running){
        deltaTime = SDL_GetTicks64() - deltaPrev;
        deltaPrev = SDL_GetTicks64();

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

                        UIElements_Generate();
                    }

                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        printf("LeftClick");

                        target.x = event.button.x;
                        target.y = event.button.y;
                    }


                default:
                    break;
            }
        }
        if (timer_forceRender + FPS < SDL_GetTicks64()){
            timer_forceRender = SDL_GetTicks64();

            #pragma region DrawScreen
            switch (GetGamestate())
            {
            case GS_TitleScreen:
                if (gamestate_timer == 0) gamestate_timer = SDL_GetTicks64() + GS_TitleScreen_Durration;
                if (gamestate_timer < SDL_GetTicks64()) {
                    SetGameState(GS_MainMenu); 
                    UIElements_Generate();
                    gamestate_timer = 0; 
                    break; 
                }

                SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 255);
                SDL_RenderClear(MainRenderer);
                
                Render_UIElements();

                break;
            
            case GS_MainMenu:
        
                SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
                SDL_RenderClear(MainRenderer);

                Render_UIElements();

        

                SDL_SetRenderDrawColor(MainRenderer, 255, 255, 0, 0);
                p = LerpVect(p, target, 1, deltaTime);

                SDL_Rect rect;
                rect.w = 10;
                rect.h = 10;
                rect.x = p.x;
                rect.y = p.y;
                SDL_RenderDrawRect(MainRenderer, &rect);
                
    

                break;
            case GS_SudokuState:
                switch (GetSudokustate())
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

            SDL_RenderPresent(MainRenderer);
        }

        SDL_Delay(1);
    }

    EXECUTE_CLEANUP();
    TTF_CloseFont(GetFont());
    SDL_Quit();

    return 0;
}
