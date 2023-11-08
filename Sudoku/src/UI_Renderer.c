#include "UI_Renderer.h"

void Renderer_Init(){
    pipeline_count = 0;
    pipeline_total = 0;

    TryFree(RenderPipeline);
    RenderPipeline = malloc(0);
}
void Render_TextureElement(struct UI_TextureElement *element){
    SetErrorIndentfyer("UI_Renderer_RenderTexture: element null"); malloc_verify(element);
    int succ = SDL_RenderCopy(MainRenderer, element->texture, NULL, &(element->rect));
    SetErrorIndentfyer("UI_Renderer_RenderTexture"); SDL_verify(succ);
}

void Pipeline_remalloc(int elementsToAdd){
    if (pipeline_count + elementsToAdd < pipeline_total) return;

    pipeline_total = pipeline_count + elementsToAdd;
    RenderPipeline = realloc(RenderPipeline, pipeline_total * sizeof(UI_Element));


}

void Pipeline_Append(struct UI_Element *element){
    if(pipeline_count == pipeline_total) Pipeline_remalloc(1);

}

void Renderer_RenderPipeline(){

}