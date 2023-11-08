#include "UI_Elements.h"

struct UI_TextureElement *TitleScreen;
struct UI_TextureElement *Title;

int TriggerAreaID_count;
int *TriggerAreaIDs;

void UIElements_Init(){
    TitleScreen = malloc(sizeof(UI_TextureElement));
    SetErrorIndentfyer("UI_Elements: GENS_TitleScreen"); malloc_verify(TitleScreen);
    GC_Append(TitleScreen);

    SDL_Color TitleScreen_color = {0, 0, 0, 255};
    TitleScreen->color = TitleScreen_color;

    Title = malloc(sizeof(UI_TextureElement));
    SetErrorIndentfyer("UI_Elements: GENS_Title"); malloc_verify(Title);
    GC_Append(Title);

    SDL_Color title_color = MainColor_Green;
    Title->color = title_color;

    TriggerAreaID_count = 0;
    TriggerAreaIDs = malloc(0);
}

void UIElements_GenerateStatic(){
    #pragma region TitleScreen
    if (GetGamestate() == GS_TitleScreen){
        SDL_Color TS_fg = TitleScreen->color;
        int TS_w, TS_h;
        TitleScreen->texture = RenderFont(MainRenderer, GetFont(), TITLE_SCREEN, TS_fg, &TS_w, &TS_h);
        SDL_Rect TS_rect;
            TS_rect.w = (int)SDL_round(MainWindowWidth * 0.4);
            TS_rect.h = (int)SDL_round(((double)TS_rect.w / TS_w) * TS_h);
            TS_rect.x = (int)SDL_round((MainWindowWidth / 2.0) - (TS_rect.w / 2));
            TS_rect.y = (int)SDL_round((MainWindowHeight / 2.0) - (TS_rect.h / 2));
        TitleScreen->rect = TS_rect;
    }
    #pragma endregion

    #pragma region Title
    if(GetGamestate() == GS_MainMenu){
        SDL_Color Title_fg = Title->color;
        int Tile_w, Title_h;
        Title->texture = RenderFont(MainRenderer, GetFont(), TITLE_SCREEN, Title_fg, &Tile_w, &Title_h);
        SDL_Rect Title_rect;
            Title_rect.w = (int)SDL_round(MainWindowWidth * 0.3);
            Title_rect.h = (int)SDL_round(((double)Title_rect.w / Tile_w) * Title_h);
            Title_rect.x = (int)SDL_round((MainWindowWidth / 2.0) - (Title_rect.w / 2));
            Title_rect.y = (int)SDL_round((MainWindowHeight * 0.03));
        Title->rect = Title_rect;
    }
    #pragma endregion
}

bool InTriggerAreaOfElement(struct UI_Element *element, SDL_Point point){
    struct Shape *shapes = element->trigger.triggerArea.shapes;
    for(int shape_index = 0; shape_index < element->trigger.triggerArea.shapeCount; shape_index++){
        struct Shape *currentShape = &(shapes[shape_index]);
        for (int i = 0; i < currentShape->height; i++)
        {
            int y = element->posY + currentShape->offset_Y + i;

            if (point.y != y) continue;

            int x_start = element->posX + currentShape->offset_X + currentShape->boundrary_start[i];
            int x_end   = element->posX + currentShape->offset_X +   currentShape->boundrary_end[i];

            if (point.x > x_start && point.x < x_end) return true;
        }
    }
    return false;
}

void UIElements_Generate(struct UI_Element *renderedElements, int element_count, SDL_Point cursorPos, int TriggerAreaID){
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
                fg.rect.x = (width / 2) - (fg.rect.w / 2);
                fg.rect.h = (height / 2) - (fg.rect.h / 2);

                StartButton->foreground = fg;
                StartButton->has_fg = true;
            
            StartButton->has_anim = false;

            
        }
        #pragma endregion

        #pragma 
    }
    #pragma endregion
}