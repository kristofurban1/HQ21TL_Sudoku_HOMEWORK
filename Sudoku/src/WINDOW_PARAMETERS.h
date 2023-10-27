#ifndef WINDOW_PARAMETERS_DEF
#define WINDOW_PARAMETERS_DEF

#include <SDL2/SDL.h>


#define SDL_FLAGS SDL_INIT_EVERYTHING
#define WindowFlags 0
#define RendererFlags SDL_RENDERER_ACCELERATED

#define WindowPosX SDL_WINDOWPOS_CENTERED
#define WindowPosY SDL_WINDOWPOS_CENTERED

#define Default_WIDTH  1280
#define Default_HEIGHT  720

#define FPS (1000/60)

extern SDL_Window *MainWindow;
extern SDL_Renderer *MainRenderer;

extern int MainWindowWidth;
extern int MainWindowHeight;

#endif