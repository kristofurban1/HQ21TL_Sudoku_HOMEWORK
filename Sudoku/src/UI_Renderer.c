#include "UI_Renderer.h"

void Render_TextureElement(struct UI_TextureElement *element){
    int succ = SDL_RenderCopy(MainRenderer, element->texture, NULL, &(element->rect));
    SetErrorIndentfyer("UI_Renderer_RenderTexture"); SDL_verify(succ);
}