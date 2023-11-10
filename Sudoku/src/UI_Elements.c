#include "UI_Elements.h"

#define COLOR_Green         {102, 255, 0, 250}
#define COLOR_White         {255, 255, 255, 255}
#define COLOR_Black         {0, 0, 0, 255}
#define COLOR_DarkGreen     {70, 200, 30, 100}

#define TITLE "SUDOKU"
#define START_LABEL "Play"

SDL_Color C_Green       = COLOR_Green;
SDL_Color C_White       = COLOR_White;
SDL_Color C_Black       = COLOR_Black;
SDL_Color C_DarkGreen   = COLOR_DarkGreen;

int TriggerAreaID_count;
int *TriggerAreaIDs;

int ElementCount;
struct UI_Element **UI_Elements;

void FreeUI_Element(struct UI_Element *element){
    if (element->hasLabel){
        SDL_DestroyTexture(element->label.texture);
    }

    struct UI_ElementShape *es_T = NULL;
    struct UI_ElementShape *es_B = NULL;
    if(element->hasTrigger){
        es_T = element->trigger.area;
        TryFree(element->trigger.area);
    }

    if (element->hasBackground && es_T != element->background) es_B = element->background;

    if (es_T != NULL){
        for (int i = 0; i < es_T->shapeCount; i++)
        {
            TryFree(es_T->shapes[i]->boundrary_start);
            TryFree(es_T->shapes[i]->boundrary_end);
            TryFree(es_T->shapes[i]);
        }
    }

    if (es_B != NULL){
        for (int i = 0; i < es_B->shapeCount; i++)
        {
            TryFree(es_B->shapes[i]->boundrary_start);
            TryFree(es_B->shapes[i]->boundrary_end);
            TryFree(es_B->shapes[i]);
        }
    }

    TryFree(element);
}

void ResetElements(){
    TryFree(TriggerAreaIDs);

    for(int i = 0; i < ElementCount; i++) FreeUI_Element(UI_Elements[i]);
    TryFree(UI_Elements);
    
    TriggerAreaID_count = 0;
    TriggerAreaIDs = malloc(0);

    ElementCount = 0;
    UI_Elements = malloc(0);
}

void UIElements_Generate(){
    ResetElements();
    #pragma region TitleScreen
    if (GetGamestate() == GS_TitleScreen){
        SetErrorIndentfyer("UIGen: TitleScreen");

        struct UI_Element *TitleScreen = malloc(sizeof(UI_Element)); 
            malloc_verify(TitleScreen);
        
        TitleScreen->UniqueID = 0;

        TitleScreen->hasAnim = false;
        TitleScreen->hasTrigger = false;
        TitleScreen->TriggerCallback = NULL;
        TitleScreen->hasBackground = false;

        TitleScreen->pos.x = MainWindowWidth  * 0.5;
        TitleScreen->pos.y = MainWindowHeight * 0.5;
        TitleScreen->pos.width  = MainWindowWidth * 0.4;
        TitleScreen->pos.height =  MainWindowHeight;

        TitleScreen->hasLabel = true;
        TitleScreen->label.visible = true;
        char *LabelText = TITLE;
        TitleScreen->label.text = LabelText;
        TitleScreen->label.makeFit = false;
        TitleScreen->label.preferWidthOverHeight = true;
        TitleScreen->label.targetSize_W = TitleScreen->pos.width;
        TitleScreen->label.targetSize_H = -1;
        TitleScreen->label.fgcolor = C_Black;
        TitleScreen->label.texture = NULL;


        ElementCount = 1;
        UI_Elements = malloc( ElementCount * sizeof(struct UI_Element));
            malloc_verify(UI_Elements);
        UI_Elements[0] = TitleScreen;
        return;
    }
    #pragma endregion

    #pragma region Title
    if(GetGamestate() == GS_MainMenu){
        SetErrorIndentfyer("UIGen: MainMenu");
        struct UI_Element *Title         = malloc(sizeof(UI_Element)); 
        struct UI_Element *StartButton   = malloc(sizeof(UI_Element)); 

        #pragma region Title
            Title->UniqueID = 10;
            
            Title->hasAnim = false;
            Title->hasTrigger = false;
            Title->TriggerCallback = NULL;
            Title->hasBackground = false;

            Title->pos.x = MainWindowWidth  * 0.5;
            Title->pos.y = MainWindowHeight * 0.1;
            Title->pos.width  = MainWindowWidth * 0.2;
            Title->pos.height =  MainWindowHeight;

            Title->hasLabel = true;
            Title->label.visible = true;
            char *T_LabelText = TITLE;
            Title->label.text = T_LabelText;
            Title->label.makeFit = false;
            Title->label.preferWidthOverHeight = true;
            Title->label.targetSize_W = Title->pos.width;
            Title->label.targetSize_H = -1;
            Title->label.fgcolor = C_Green;
            Title->label.texture = NULL;
        #pragma endregion

        #pragma region StartButton
            StartButton->UniqueID = 11;

            StartButton->hasAnim = false;
            StartButton->hasLabel = true;
            StartButton->hasBackground = true;
            StartButton->hasTrigger = true;

            StartButton->pos.x = MainWindowWidth * 0.5;
            StartButton->pos.y = MainWindowWidth * 0.8;
            StartButton->pos.width = MainWindowWidth * 0.15;
            StartButton->pos.height = MainWindowHeight * 0.05;

            StartButton->label.visible = true;
            char *SB_LabelText = START_LABEL;
            StartButton->label.text = SB_LabelText;
            StartButton->label.texture = NULL;
            StartButton->label.makeFit = true;
            StartButton->label.targetSize_W = StartButton->pos.width * 0.7;
            StartButton->label.targetSize_H = StartButton->pos.height * 0.9;
            StartButton->label.fgcolor = C_Black;
            StartButton->fgcolor = C_Black;
            StartButton->t_fgcolor = C_White;

            struct UI_ElementShape *btnShape = malloc(sizeof(struct UI_ElementShape));
                malloc_verify(btnShape);
                struct Shape shape;
                    shape.height = StartButton->pos.height;
                    shape.offset_X = 0;
                    shape.offset_Y = 0;
                    shape.boundrary_start = malloc(StartButton->pos.height * sizeof(int)); malloc_verify(shape.boundrary_start);
                    int *b_start = shape.boundrary_start;
                    shape.boundrary_end = malloc(StartButton->pos.height * sizeof(int)); malloc_verify(shape.boundrary_end);
                    int *b_end = shape.boundrary_end;

                    for (int i = 0; i < 90; i++)
                    {
                        float rad = i * (M_PI / 180);
                        int y = (StartButton->pos.height/2) * sin(rad);
                        int x = (StartButton->pos.height/2) * cos(rad);

                        b_start[(StartButton->pos.height / 2) - y] = StartButton->pos.height - x;
                        b_start[(StartButton->pos.height / 2) + y] = StartButton->pos.height - x;

                        b_end[(StartButton->pos.height / 2) - y] = StartButton->pos.width - (StartButton->pos.height - x);
                        b_end[(StartButton->pos.height / 2) + y] = StartButton->pos.width - (StartButton->pos.height - x);
                    }
                    

                btnShape->shapeCount = 1;

                btnShape->shapes = malloc(btnShape->shapeCount * sizeof(Shape));
                    malloc_verify(btnShape->shapes);
                    btnShape->shapes[0] = &shape;
            
            StartButton->background = btnShape;
            StartButton->bgcolor = C_Green;
            StartButton->t_bgcolor = C_DarkGreen;

            StartButton->trigger.area = btnShape;
            StartButton->trigger.enabled = true;
            StartButton->trigger.TriggerAreaID = 1;


            ;
        #pragma endregion

        ElementCount = 2;
        UI_Elements = malloc( ElementCount * sizeof(struct UI_Element));
            malloc_verify(UI_Elements);
        UI_Elements[0] = Title;
        UI_Elements[1] = StartButton;
        return;
    }
    #pragma endregion
}

/*
bool InTriggerAreaOfElement(struct UI_Trigger *trigger, SDL_Point point){
    struct Shape *shapes = trigger->area.shapes;
    for(int shape_index = 0; shape_index < trigger->area.shapeCount; shape_index++){
        struct Shape *currentShape = &(shapes[shape_index]);
        for (int i = 0; i < currentShape->height; i++)
        {
            int y = trigger->area.pos.y + currentShape->offset_Y + i;

            if (point.y != y) continue;

            int x_start = trigger->area.pos.x + currentShape->offset_X + currentShape->boundrary_start[i];
            int x_end   = trigger->area.pos.x + currentShape->offset_X +   currentShape->boundrary_end[i];

            if (point.x > x_start && point.x < x_end) return true;
        }
    }
    return false;
}

struct UI_Element *UIElements_Generate(int *element_count, SDL_Point cursorPos, int TriggerAreaID){
    #pragma region MainMenu
    if (GetGamestate() == GS_MainMenu){
        #pragma region StartButton
        struct UI_Element *StartButton = malloc(sizeof(UI_Element));
        SetErrorIndentfyer("UI_Elements: Generate Startbutton"); malloc_verify(StartButton);
        {
            char *fg_text = "Play";
            int width = MainWindowWidth * 0.3;
            int height = width * 0.1;
            int posX = (MainWindowWidth / 2) - (width / 2);
            int posY = (MainWindowHeight * 0.70) - (height / 2);
            
            StartButton.background = posX;
            StartButton->posY = posY;

            struct UI_ElementShape btnShape;
                struct Shape shape;
                    shape.height = height;
                    shape.offset_X = 0;
                    shape.offset_Y = 0;
                    shape.boundrary_start = malloc(height * sizeof(int)); malloc_verify(shape.boundrary_start);
                    int *b_start = shape.boundrary_start;
                    shape.boundrary_end = malloc(height * sizeof(int)); malloc_verify(shape.boundrary_end);
                    int *b_end = shape.boundrary_end;

                    for (int i = 0; i < 90; i++)
                    {
                        float rad = i * (M_PI / 180);
                        int y = (height/2) * sin(rad);
                        int x = (height/2) * cos(rad);

                        b_start[(height / 2) - y] = height - x;
                        b_start[(height / 2) + y] = height - x;

                        b_end[(height / 2) - y] = width - (height - x);
                        b_end[(height / 2) + y] = width - (height - x);
                    }
                    

                btnShape.shapeCount = 1;

                btnShape.shapes = malloc(btnShape.shapeCount * sizeof(Shape));
                    malloc_verify(btnShape.shapes);
                struct Shape *shapes_ptr = btnShape.shapes;
                    shapes_ptr[0] = shape;
            
            StartButton->has_trigger = true;
            StartButton->trigger.triggerArea = btnShape;
            StartButton->trigger.TriggerAreaID = 1;
            if (TriggerAreaID == -1 && cursorPos.x+cursorPos.y != -2){
                StartButton->trigger.isTriggered = InTriggerAreaOfElement(StartButton, cursorPos);
            }
            else if(TriggerAreaID == StartButton->trigger.TriggerAreaID){
                StartButton->trigger.isTriggered = true;
            }

            SDL_Color bg_color = MainColor_Green;
            StartButton->bgcolor = bg_color;
            if (StartButton->has_trigger && StartButton->trigger.isTriggered)
                StartButton->bgcolor = StartButton->trigger.triggeredColor2;

            StartButton->background = btnShape;

            struct UI_TextureElement fg;
                SDL_Color fg_color = AccentColor_White;
                fg.color =  fg_color;
                if (StartButton->has_trigger && StartButton->trigger.isTriggered)
                    fg.color = StartButton->trigger.triggeredColor1;
                
                int fgw, fgh;
                fg.texture = RenderFont(MainRenderer, GetFont(), fg_text, fg.color, &fgw, &fgh);

                fg.rect.w = width * 0.5;
                fg.rect.h = (fg.rect.w / (float)fgw) * fgh;
                if (fg.rect.h + (fg.rect.h * 1.1) > height){
                    fg.rect.h = height / 1.1;
                    fg.rect.w = (fg.rect.h / (float)fgh) * fgw;
                }
                fg.rect.x = posX + ((width  / 2) - (fg.rect.w / 2));
                fg.rect.h = posY + ((height / 2) - (fg.rect.h / 2));

                StartButton->foreground = fg;
                StartButton->has_fg = true;
            

            
        }
            
        #pragma endregion
        
        #pragma region MainMenu_RETURN

        *element_count = 1;  
        struct UI_Element **rendered_elements = malloc(*element_count * sizeof(struct UI_Element *));
        SetErrorIndentfyer("UIElements:Generate ReturnMainMenu"); malloc_verify(*rendered_elements);
        rendered_elements[0] = StartButton;

        return rendered_elements;
        #pragma endregion
    }
    #pragma endregion
}
*/