#include "UI_Renderer.h"

void Render_TextureElement(struct UI_TextureElement *element){
    SDL_RenderCopy(MainRenderer, element->texture, NULL, &(element->rect));
}