#ifndef UIRenderer_DEF
#define UIRenderer_DEF

#include "WINDOW_PARAMETERS.h"
#include "UI_Elements.h"
#include "debugmalloc.h"

#include <SDL2/SDL.h>


extern void Render_Label(struct UI_Label *label);

extern void Render_UIElements();


#endif