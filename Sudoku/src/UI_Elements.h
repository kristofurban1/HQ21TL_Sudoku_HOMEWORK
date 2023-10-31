#ifndef UIElements_DEF
#define UIElements_DEF

#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "Cleanup.h"
#include "FontManager.h"
#include "debugmalloc.h"
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#define TITLE_SCREEN "SUDOKU"
extern struct UI_TextureElement *TitleScreen;
extern struct UI_TextureElement *Title;

extern struct Element_Shape{
    int offset_X, offset_Y;
    int height;
    int *boundrary_start;
    int *boundrary_end;
} Element_Shape;

extern struct UI_Element{
    int posX, posY;
    struct Element_Shape *shapes; int shapeCount;
} UI_Element;

extern struct UI_TextureElement{
    SDL_Rect rect;
    SDL_Texture *texture;
} UI_TextureElement;

extern void UIElements_Init();

extern void UIElements_GenerateStatic();

#endif