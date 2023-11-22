#include "main.h"

#define SHOW_SCREEN_DIV true

int MainWindowWidth  = Default_WIDTH;
int MainWindowHeight = Default_HEIGHT;
SDL_Window *MainWindow      = NULL;
SDL_Renderer *MainRenderer  = NULL;

extern int main(int argc, char *argv[]) {
    srand(time(NULL));
    GC_Init();          // GarbageCollector
    INITIALIZE_ALL();   // SDL
    FileHandler_Init(); // FileHandler
    FontManager_Init(); // FontManager
    ResetElements();  // UI_Elements
    Gamestate_Init();   // Gamestate

    SetBoardSize(3);
    printf("BS: %d\n", GetBoardSize());

    SDL_SetWindowTitle(MainWindow, WINDOW_TITLE);
    SDL_Surface *icon = IMG_Load(GetAsset(ASSET_ICON));
    SDL_SetWindowIcon(MainWindow, icon);
    SDL_FreeSurface(icon);

    UIElements_Generate();
    Interface_InitCurrentState();

    Uint64 timer_forceRender = SDL_GetTicks64();
    Uint64 gamestate_timer = 0;

    bool running = true;
    Uint64 deltaTime_ms = 0;
    Uint64 deltaPrev = SDL_GetTicks64();
    while(running){
        deltaTime_ms = SDL_GetTicks64() - deltaPrev;
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
                        Interface_InitCurrentState();
                    }

                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        printf("Mouse: LeftClick\n");
                        SDL_Point clickpos;
                        clickpos.x = event.button.x;
                        clickpos.y = event.button.y;
                        Interface_EventHandler_Mouse(clickpos);
                    }
                    break;
                case SDL_KEYDOWN:
                    printf("Keyboard: Buttonpress: %d\n", event.key.keysym.scancode);
                    Interface_EventHandler_Keyboard(event.key.keysym.scancode);
                    break;

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
                    Interface_InitCurrentState();
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
                
                break;
            case GS_SudokuState:
                switch (GetSudokustate())
                    {
                    case GS_Sudoku:
                        SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
                        SDL_RenderClear(MainRenderer);
                        Render_UIElements();
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

            if (SHOW_SCREEN_DIV){
                SDL_SetRenderDrawColor(MainRenderer, 50, 50, 50, 255);
                for (int i = 0; i <= 10; i++)
                {
                    float p = i * 0.1;
                    
                    SDL_RenderDrawLine(MainRenderer, (int)(MainWindowWidth * p), 0, (int)(MainWindowWidth * p), MainWindowHeight);
                    SDL_RenderDrawLine(MainRenderer, 0, (int)(MainWindowHeight * p), MainWindowWidth, (int)(MainWindowHeight * p));

                }
            }

            SDL_RenderPresent(MainRenderer);
        }

        SDL_Delay(1);
    }

    ResetElements();
    EXECUTE_CLEANUP();
    TTF_CloseFont(GetFont());
    SDL_Quit();

    return 0;
}
