//#ifndef WINDOW_PARAMETERS_DEF
#define WINDOW_PARAMETERS_DEF

#include <SDL2/SDL.h>

#define WINDOW_TITLE "Variable Sudoku - UKT"

#define SDL_FLAGS SDL_INIT_EVERYTHING
#define WindowFlags SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
#define RendererFlags SDL_RENDERER_ACCELERATED

#define WindowPosX SDL_WINDOWPOS_CENTERED
#define WindowPosY SDL_WINDOWPOS_CENTERED

#define Default_WIDTH   800
#define Default_HEIGHT  600

#define Minimum_Width  300
#define Minimum_Heigth 500

#define FPS (1000/60)

extern SDL_Window *MainWindow;
extern SDL_Renderer *MainRenderer;

extern int MainWindowWidth;
extern int MainWindowHeight;

//#endif