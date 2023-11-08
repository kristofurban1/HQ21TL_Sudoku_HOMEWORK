#ifndef UIRenderer_DEF
#define UIRenderer_DEF

#include "WINDOW_PARAMETERS.h"
#include "UI_Elements.h"
#include "debugmalloc.h"

#include <SDL2/SDL.h>

static int pipeline_count = 0;
static int pipeline_total = 0; 
static struct UI_Element *RenderPipeline;

extern void Renderer_Init();

extern void Pipeline_remalloc(int elementsToAdd);
extern void Pipeline_Append(struct UI_Element *element);
extern void Renderer_RenderPipeline();

extern void Render_TextureElement(struct UI_TextureElement *element);

#endif