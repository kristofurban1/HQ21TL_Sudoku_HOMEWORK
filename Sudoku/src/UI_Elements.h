#ifndef UIElements_DEF
#define UIElements_DEF

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "Cleanup.h"
#include "FontManager.h"
#include "animation_handler.h"
#include "GameState.h"
#include "debugmalloc.h"
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#define MainColor_Green {102, 255, 0, 250}
#define AccentColor_White {255, 255, 255, 255}
#define TriggeredColor_DarkGreen {70, 200, 30, 100}

#define TITLE_SCREEN "SUDOKU"
extern struct UI_TextureElement *TitleScreen;
extern struct UI_TextureElement *Title;

extern int TriggerAreaID_count;
extern int *TriggerAreaIDs;

extern struct Shape{
    int offset_X, offset_Y;
    int height;
    int *boundrary_start;
    int *boundrary_end;
} Shape;

extern struct UI_ElementShape{
    struct Shape *shapes; 
    int shapeCount;
} UI_ElementShape;

extern struct UI_TriggerElement{
    int TriggerAreaID;
    struct UI_ElementShape triggerArea;
    bool isTriggered;
    SDL_Color triggeredColor1;
    SDL_Color triggeredColor2;

} UI_TriggerElement;

extern struct UI_TextureElement{
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Color color;
} UI_TextureElement;

extern struct UI_Element{
    int posX, posY;
    SDL_Color bgcolor;
    struct UI_ElementShape background;
    bool has_trigger;
    struct UI_TriggerElement trigger;
    bool has_anim;
    struct Animation anim;
    bool has_fg;
    struct UI_TextureElement foreground;
} UI_Element;

extern void UIElements_Init();



extern void UIElements_GenerateStatic();

extern bool InTriggerAreaOfElement(struct UI_Element *element, SDL_Point point);

void UIElements_Generate(struct UI_Element *renderedElements, int element_count, SDL_Point cursorPos, int TriggerAreaID);

#endif