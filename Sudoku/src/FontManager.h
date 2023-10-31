#ifndef FontManager_DEF
#define FontManager_DEF

#include "ErrorHandler.h"
#include "file_handler.h"

#include "debugmalloc.h"

#include <SDL2/SDL_ttf.h>

#define FontSize 500
extern TTF_Font *__FONT__;

extern TTF_Font *LoadFont(int size);

extern SDL_Texture *RenderFont(SDL_Renderer *renderer, TTF_Font *font, char *text, SDL_Color fg, int *width, int *height);

extern TTF_Font *GetFont();

extern void FontManager_Init();

#endif