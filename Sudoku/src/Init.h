#ifndef INIT_DEF
#define INIT_DEF

#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "Cleanup.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


/*
    @brief Initializes every startup module.
    @note Requires no additional memory.
    @attention Run only once.
*/
extern void INITIALIZE_ALL();

/*
    @brief Initalizes the SDL module.
    @attention Runs only once. Is included in INITIALIZE_ALL.
    @param flags SDL Subsystems to initialize.
*/
extern void Init_SDL(Uint32 flags);


extern void Init_TTF();

/*
    @brief Creates a new window.

    @param window Pointer to created window.
    @param WinPosX Location X
    @param WinPosY Location Y
    @param Width Width of window
    @param Height Height of window
    @param flags Window flags.

    @exception
        Requires valid position and size, position must be inside display dimensions, and size cannot exceed 16384 x 16384.
    @exception
        OpenGL, Vulcan, Metal are not initialized. Do not set flags that make use of those libraries.
*/
extern void Create_Window(SDL_Window **window, int WinPosX, int WinPosY, int Width, int Height, SDL_WindowFlags flags);

/*
    @brief Creates a new renderer.
    @param target_window The window associated with renderer.
    @param renderer Pointer to the created renderer.
    @param flags Renderer flags
*/
extern void Create_Renderer(SDL_Window *target_window, SDL_Renderer **renderer, SDL_RendererFlags flags);


#endif