#include "UI_Renderer.h"

void Render_UIElementShape(struct UI_ElementShape *elementShape, struct UI_Pos *pos){
    if (!elementShape->visible) return;

    SDL_SetRenderDrawColor(MainRenderer, 
        elementShape->bgcolor.r, 
        elementShape->bgcolor.g, 
        elementShape->bgcolor.b, 
        elementShape->bgcolor.a
    );
    
    for (int shape_index = 0; shape_index < elementShape->shapeCount; shape_index++)
    {
        struct Shape *current = elementShape->shapes[shape_index];

        int _Y = (pos->y - (current->height / 2)) + current->offset_Y;
        int _X = current->offset_X + pos->x  - (current->width / 2);

        for (int y = 0; y < current->height; y++)
        {
            int Y = _Y + y;

            int X_start = current->boundrary_start[y] + _X;
            int X_end   = current->boundrary_end[y]   + _X;

            SDL_RenderDrawLine(MainRenderer, X_start, Y, X_end, Y);
        }
    }
    
}

void RenderLabel(struct UI_Label *label, struct UI_Pos *pos){
    if (!label->visible) return;
    int w, h;
    label->texture = RenderFont(MainRenderer, GetFont(), label->text, label->fgcolor, &w, &h);

    if (label->makeFit){
        label->rect.w = label->targetSize_W;
        label->rect.h =  (label->rect.w / (float)w) * h;
        if (label->rect.h > label->targetSize_H){
            label->rect.h = label->targetSize_H;
            label->rect.w =  (label->rect.h / (float)h) * w;
        }
    }
    else{
        if (label->preferWidthOverHeight){
            label->rect.w = label->targetSize_W;
            label->rect.h =  (label->rect.w / (float)w) * h;
        }
        else{
            label->rect.h = label->targetSize_H;
            label->rect.w =  (label->rect.h / (float)h) * w;
        }
    }

    label->rect.x = pos->x - (label->rect.w / 2);
    label->rect.y = pos->y - (label->rect.h / 2);

    int succ = SDL_RenderCopy(MainRenderer, label->texture, NULL, &(label->rect));
    SetErrorIndentfyer("UI_Renderer: RenderLabel"); SDL_verify(succ);
}

void Render_UIElements(){
    for (int element_index = 0; element_index < ElementCount; element_index++)
    {
        struct UI_Element *current = UI_Elements[element_index];

        //current->hasTrigger
    }
    
}

/*
void Render_TextureElement(struct UI_TextureElement *element){
    SetErrorIndentfyer("UI_Renderer_RenderTexture: element null"); malloc_verify(element);
    int succ = SDL_RenderCopy(MainRenderer, element->texture, NULL, &(element->rect));
    SetErrorIndentfyer("UI_Renderer_RenderTexture"); SDL_verify(succ);
}

void RenderElements(SDL_Point cursorPos, int TriggerAreaID){
    int elementCount;
    struct UI_Element **elements = UIElements_Generate(&elementCount, cursorPos, TriggerAreaID);

    for (int i = 0; i < elementCount; i++)
    {
        struct UI_Element *element = elements[i];
        
        #pragma region BG
            struct Shape *shapes = element->background.shapes;
            SDL_Color *bg_color = &(element->bgcolor);
            SDL_SetRenderDrawColor(MainRenderer, bg_color->r, bg_color->g, bg_color->b, bg_color->a);
            for (int i = 0; i < element->background.shapeCount; i++)
            {
                struct Shape *shape = &(shapes[i]);

                int *b_start = (shape->boundrary_start);
                int *b_end   = (shape->boundrary_end);

                for (int _h = 0; _h < shape->height; _h++)
                {
                    int Y = element->posY + shape->offset_Y + _h;

                    int X_start = element->posX + shape->offset_X + b_start[_h];
                    int X_end   = element->posX + shape->offset_X +   b_end[_h];

                    SDL_RenderDrawLine(MainRenderer, X_start, Y, X_end, Y);
                }

                TryFree(b_end);
                TryFree(b_start);
                TryFree(shape);
            }
            TryFree(shapes);
        #pragma endregion

        Render_TextureElement(&(element->foreground));

        


        TryFree(element);
    }
    TryFree(elements);
    
}
*/