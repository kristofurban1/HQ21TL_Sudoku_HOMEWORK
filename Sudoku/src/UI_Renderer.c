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

void Render_Label(struct UI_Label *label, struct UI_Pos *pos){
    int w, h;
    label->texture = RenderFont(MainRenderer, GetFont(), label->text, label->fgcolor, &(w), &(h));

    if (label->makeFit){
        label->rect.w = label->targetSize_W;
        label->rect.h =  (label->rect.w / (float)w) * h;
        if (label->rect.h > label->targetSize_H){
            label->rect.h = label->targetSize_H;
            label->rect.w =  (label->rect.h / (float)w) * h;
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

    label->rect.x = pos->x - (label->rect.w / 2) + label->offset_X;
    label->rect.y = pos->y - (label->rect.h / 2) + label->offset_Y;
    
    

}

void Render_UIElements(Uint64 deltatime_ms){
    for (int element_index = 0; element_index < ElementCount; element_index++)
    {
        struct UI_Element *current = UI_Elements[element_index];

        if (current->label.texture == NULL)
            Render_Label(&(current->label), &(current->pos));

        if(current->hasBackground){

            Render_UIElementShape(current->background, &(current->pos));
        }

        if(current->hasLabel && current->label.visible)
        {
            SetErrorIndentfyer("UI_Renderer: RenderLabel"); 
            SDL_verify( SDL_RenderCopy(MainRenderer, current->label.texture, NULL, &(current->label.rect)));
        }

        if (current->trigger.isTriggered){
            current->trigger.trigger_stay_ms -= deltatime_ms;
            if (current->trigger.trigger_stay_ms <= 0){
                current->trigger.isTriggered = false;
                if (current->hasBackground) current->background->bgcolor = current->bgcolor;
                if (current->hasLabel) current->label.fgcolor = current->fgcolor;
            }

        }

    }
    
}