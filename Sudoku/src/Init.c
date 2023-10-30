#include "Init.h"

void Init_SDL(Uint32 flags){
    SetErrorIndentfyer("SDL Initialization.");
    SDL_verify(SDL_Init(flags));
}

void Create_Window(SDL_Window **window, int WinPosX, int WinPosY, int Width, int Height, SDL_WindowFlags flags){
    *window = SDL_CreateWindow("SLD test", WinPosX, WinPosY, Width, Height, flags);
    SetErrorIndentfyer("SDL Window Creation.");
    SDL_ptr_verify(MainWindow);

    GC_AppendWindow(window);
}

void Create_Renderer(SDL_Window *target_window, SDL_Renderer **renderer, SDL_RendererFlags flags){
    *renderer = SDL_CreateRenderer(target_window, -1, flags);
    SetErrorIndentfyer("SDL Renderer Creation.");
    SDL_ptr_verify(renderer);

    GC_AppendRenderer(renderer);
}

void Init_TTF(){
    SetErrorIndentfyer("TTF Initialization.");
    SDL_verify(TTF_Init());
}

void INITIALIZE_ALL(){
    Init_SDL(SDL_FLAGS);
    Create_Window(&MainWindow, WindowPosX, WindowPosY, MainWindowWidth, MainWindowHeight, WindowFlags);
    Create_Renderer(MainWindow, &MainRenderer, RendererFlags);
    Init_TTF();
}