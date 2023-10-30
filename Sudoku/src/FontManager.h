#ifndef FontManager_DEF
#define FontManager_DEF

#include "ErrorHandler.h"
#include "file_handler.h"

#include <SDL2/SDL_ttf.h>

extern TTF_Font *LoadFont(int size);

extern SDL_Texture *RenderFont(SDL_Renderer *renderer, TTF_Font *font, char *text, SDL_Color fg, int *width, int *height);

#endif