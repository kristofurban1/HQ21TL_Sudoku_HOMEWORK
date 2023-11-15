#include "UI_Elements.h"

#define COLOR_Green         {102, 255, 0, 250}
#define COLOR_DarkGreen     {70, 200, 30, 100}
#define COLOR_White         {255, 255, 255, 255}
#define COLOR_Gray          {80, 80, 80, 255}
#define COLOR_Black         {0, 0, 0, 255}

#define TITLE "SUDOKU"
#define START_LABEL "Play"
#define BACK_LABEL "Back"

SDL_Color C_Green       = COLOR_Green;
SDL_Color C_DarkGreen   = COLOR_DarkGreen;
SDL_Color C_White       = COLOR_White;
SDL_Color C_Gray        = COLOR_Gray;
SDL_Color C_Black       = COLOR_Black;

int ElementCount;
struct UI_Element **UI_Elements;

struct UI_Element *UI_GetByID(int uniqueID){
    for (int i = 0; i < ElementCount; i++)
        if (UI_Elements[i]->UniqueID == uniqueID) return (UI_Elements[i]);
    
    return NULL;
}

struct UI_Element **UIs_GetByTAID(int triggerAreaID, int *match_count){
    SetErrorIndentfyer("UI_GetByTAID");
    struct UI_Element **matches = malloc(sizeof(UI_Element) * ElementCount);
        malloc_verify(matches);
    *match_count = 0;
    for (int i = 0; i < ElementCount; i++){
        if (!UI_Elements[i]->hasTrigger) continue;

        if (UI_Elements[i]->trigger.TriggerAreaID == triggerAreaID){
            matches[*match_count] = UI_Elements[i];
            (*match_count)++;
        }
    }
    matches = realloc(matches, sizeof(struct UI_Element) * (*match_count));
        malloc_verify(matches);
    return matches;
}

bool InTriggerAreaOfElement(struct UI_Element *element, SDL_Point point){
    for (int shape_index = 0; shape_index < element->trigger.area->shapeCount; shape_index++)
    {
        struct Shape *current = element->trigger.area->shapes[shape_index];

        int Y_start = (element->pos.y - (current->height / 2)) + current->offset_Y;
        int Y_end = current->height + Y_start;

        if (!(Y_start <= point.y && Y_end >= point.y)) continue;

        int _X = current->offset_X + element->pos.x  - (current->width / 2);

        int X_start = current->boundrary_start[point.y - Y_start] + _X;
        int X_end   = current->boundrary_end[point.y - Y_start]   + _X;

        printf("UID: %d; MOUSE: {%d, %d}; Start:End: {%d, %d}\n", element->UniqueID, point.x, point.y, X_start, X_end);
        if (X_start <= point.x && X_end >= point.x) return true;
    }
    return false;
}

int UI_SearchForTriggeredElement(SDL_Point cursorpos){
    for (int i = ElementCount-1; i >= 0; i--){
        if (!UI_Elements[i]->hasTrigger) continue;
        printf("Search: CUID: %d\n", UI_Elements[i]->UniqueID);
        if (InTriggerAreaOfElement(UI_Elements[i], cursorpos)) return UI_Elements[i]->UniqueID;
    }
    return -1;
}

void FreeUI_Element(struct UI_Element *element){
    if (element->hasLabel){
        SDL_DestroyTexture(element->label.texture);
    }

    struct UI_ElementShape *es_T = NULL;
    struct UI_ElementShape *es_B = NULL;

    if(element->hasTrigger) es_T = element->trigger.area;
    if (element->hasBackground && es_T != element->background) es_B = element->background;
    
    if (es_T != NULL){
        for (int i = 0; i < es_T->shapeCount; i++)
        {
            TryFree(es_T->shapes[i]->boundrary_start);
            TryFree(es_T->shapes[i]->boundrary_end);
            TryFree(es_T->shapes[i]);
        }
        TryFree(es_T->shapes);
        TryFree(es_T);
    }

    if (es_B != NULL){
        for (int i = 0; i < es_B->shapeCount; i++)
        {
            TryFree(es_B->shapes[i]->boundrary_start);
            TryFree(es_B->shapes[i]->boundrary_end);
            TryFree(es_B->shapes[i]);
        }
        TryFree(es_B->shapes);
        TryFree(es_B);
    }

    TryFree(element);
}

void ResetElements(){

    for(int i = 0; i < ElementCount; i++) FreeUI_Element(UI_Elements[i]);
    TryFree(UI_Elements);

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
        TitleScreen->label.offset_X = 0;
        TitleScreen->label.offset_Y = 0;
            
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
        struct UI_Element *Title         = malloc(sizeof(UI_Element)); malloc_verify(Title);
        struct UI_Element *StartButton   = malloc(sizeof(UI_Element)); malloc_verify(StartButton);

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
            Title->label.offset_X = 0;
            Title->label.offset_Y = 0;
            Title->label.fgcolor = C_Green;
            Title->label.texture = NULL;
        #pragma endregion

                    
        #pragma region StartButton
            StartButton->UniqueID = STARTBUTTON_UID;

            StartButton->hasAnim = false;
            StartButton->hasLabel = true;
            StartButton->hasBackground = true;
            StartButton->hasTrigger = true;

            StartButton->pos.width = MainWindowWidth * 0.3;
            StartButton->pos.height = MainWindowHeight * 0.1;
            StartButton->pos.x = MainWindowWidth * 0.5;
            StartButton->pos.y = MainWindowHeight * 0.8;

            StartButton->label.visible = true;
            char *SB_LabelText = START_LABEL;
            StartButton->label.text = SB_LabelText;
            StartButton->label.texture = NULL;
            StartButton->label.makeFit = true;
            StartButton->label.targetSize_W = StartButton->pos.width * 0.7;
            StartButton->label.targetSize_H = StartButton->pos.height * 0.9;
            StartButton->label.offset_X = 0;
            StartButton->label.offset_Y = StartButton->pos.height * 0.1;
            
            StartButton->label.fgcolor = C_Gray;
            StartButton->fgcolor = C_Gray;
            StartButton->t_fgcolor = C_Green;

            struct UI_ElementShape *btnShape = malloc(sizeof(struct UI_ElementShape));
                malloc_verify(btnShape);
                btnShape->shapeCount = 1;
                btnShape->shapes = malloc(btnShape->shapeCount * sizeof(Shape));
                    malloc_verify(btnShape->shapes);
                    btnShape->shapes[0] = malloc(sizeof(struct Shape));
                        malloc_verify(btnShape->shapes[0]);
                    btnShape->shapes[0]->height = StartButton->pos.height;
                    btnShape->shapes[0]->boundrary_start = malloc(StartButton->pos.height * sizeof(int)); malloc_verify(btnShape->shapes[0]->boundrary_start);
                    int *b_start = btnShape->shapes[0]->boundrary_start;
                    btnShape->shapes[0]->boundrary_end = malloc(StartButton->pos.height * sizeof(int)); malloc_verify(btnShape->shapes[0]->boundrary_end);
                    int *b_end = btnShape->shapes[0]->boundrary_end;

                    int minS = INT32_MAX;
                    int maxE = INT32_MIN;
                    
                    for (int i = 0; i < 90; i++)
                    {
                        float rad = i * (M_PI / 180);
                        int y = (StartButton->pos.height/2) * sin(rad);
                        int x = (StartButton->pos.height/2) * (1 - cos(rad));

                        b_start[(StartButton->pos.height / 2) - y] = x;
                        b_start[(StartButton->pos.height / 2) + y] = x;
                        
                        if (b_start[(StartButton->pos.height / 2) - y] < minS) minS = b_start[(StartButton->pos.height / 2) - y];
                        if (b_start[(StartButton->pos.height / 2) + y] < minS) minS = b_start[(StartButton->pos.height / 2) + y];

                        b_end[(StartButton->pos.height / 2) - y] = StartButton->pos.width - x;
                        b_end[(StartButton->pos.height / 2) + y] = StartButton->pos.width - x;
                        if (b_end[(StartButton->pos.height / 2) - y] > maxE) maxE = b_end[(StartButton->pos.height / 2) - y];
                        if (b_end[(StartButton->pos.height / 2) + y] > maxE) maxE = b_end[(StartButton->pos.height / 2) + y];
                    }

                    btnShape->shapes[0]->width = maxE - minS;
                    btnShape->shapes[0]->offset_X = 0;-(btnShape->shapes[0]->width/2);
                    btnShape->shapes[0]->offset_Y = 0;-(btnShape->shapes[0]->height/2);
            
            StartButton->background = btnShape;
            StartButton->background->bgcolor = C_Green;
            StartButton->bgcolor = C_Green;
            StartButton->t_bgcolor = C_DarkGreen;
            StartButton->background->visible = true;

            StartButton->trigger.area = btnShape;
            StartButton->trigger.enabled = true;
            StartButton->trigger.TriggerAreaID = 30;
            StartButton->trigger.trigger_stay_ms = 0;
            

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

    #pragma region Sudoku
    if(GetGamestate() == GS_SudokuState){
        SetErrorIndentfyer("UIGen: Sudoku");
        struct UI_Element *BackButton   = malloc(sizeof(UI_Element)); malloc_verify(BackButton);

        #pragma region BackButton
            BackButton->UniqueID = BACKBUTTON_UID;

            BackButton->hasAnim = false;
            BackButton->hasLabel = true;
            BackButton->hasBackground = true;
            BackButton->hasTrigger = true;

            BackButton->pos.width = MainWindowWidth * 0.1;
            BackButton->pos.height = MainWindowHeight * 0.05;
            BackButton->pos.x = MainWindowWidth * 0.01 + BackButton->pos.width / 2;
            BackButton->pos.y = MainWindowWidth * 0.01 + BackButton->pos.height / 2;

            BackButton->label.visible = true;
            char *BB_LabelText = BACK_LABEL;
            BackButton->label.text = BB_LabelText;
            BackButton->label.texture = NULL;
            BackButton->label.makeFit = false;
            BackButton->label.preferWidthOverHeight = false;
            BackButton->label.targetSize_W = BackButton->pos.width * 1;
            BackButton->label.targetSize_H = BackButton->pos.height * 1;
            BackButton->label.offset_X = 0;
            BackButton->label.offset_Y = BackButton->pos.height * 0.1;
            
            BackButton->label.fgcolor = C_Gray;
            BackButton->fgcolor = C_Gray;
            BackButton->t_fgcolor = C_Green;

            struct UI_ElementShape *btn1Shape = malloc(sizeof(struct UI_ElementShape));
                malloc_verify(btn1Shape);
                btn1Shape->shapeCount = 1;
                btn1Shape->shapes = malloc(btn1Shape->shapeCount * sizeof(Shape));
                    malloc_verify(btn1Shape->shapes);
                    btn1Shape->shapes[0] = malloc(sizeof(struct Shape));
                        malloc_verify(btn1Shape->shapes[0]);
                    btn1Shape->shapes[0]->height = BackButton->pos.height;
                    btn1Shape->shapes[0]->boundrary_start = malloc(BackButton->pos.height * sizeof(int)); malloc_verify(btn1Shape->shapes[0]->boundrary_start);
                    int *b_start = btn1Shape->shapes[0]->boundrary_start;
                    btn1Shape->shapes[0]->boundrary_end = malloc(BackButton->pos.height * sizeof(int)); malloc_verify(btn1Shape->shapes[0]->boundrary_end);
                    int *b_end = btn1Shape->shapes[0]->boundrary_end;


                    for (int i = 0; i < BackButton->pos.height; i++)
                    {
                        btn1Shape->shapes[0]->boundrary_start[i] = 0;
                        btn1Shape->shapes[0]->boundrary_end[i]   = BackButton->pos.width;
                    }

                    btn1Shape->shapes[0]->width = BackButton->pos.width;
                    btn1Shape->shapes[0]->offset_X = 0;
                    btn1Shape->shapes[0]->offset_Y = 0;
            
            BackButton->background = btn1Shape;
            BackButton->background->bgcolor = C_Green;
            BackButton->bgcolor = C_Green;
            BackButton->t_bgcolor = C_DarkGreen;
            BackButton->background->visible = true;

            BackButton->trigger.area = btn1Shape;
            BackButton->trigger.enabled = true;
            BackButton->trigger.TriggerAreaID = 30;
            BackButton->trigger.trigger_stay_ms = 0;
        #pragma endregion

        ElementCount = 1;
        UI_Elements = malloc( ElementCount * sizeof(struct UI_Element));
            malloc_verify(UI_Elements);
        UI_Elements[0] = BackButton;
        return;
        
    }
    #pragma endregion
}

void UpdateElementLabelText(struct UI_Element *element, char *newText){
    if (!element->hasLabel) return;
    element->label.text = newText;
    if (element->label.texture == NULL)
        SDL_DestroyTexture(element->label.texture);

    element->label.texture = NULL;
}

void AppendElement(struct UI_Element *element){
    ElementCount++;
    UI_Elements = realloc(UI_Elements, ElementCount * sizeof(struct UI_Element));
            malloc_verify(UI_Elements);
    UI_Elements[ElementCount - 1] = element;
}

void AppendElementBatch(struct UI_Element **elementlist, int appendCount){
    int startIndex = ElementCount;
    ElementCount += appendCount;
    UI_Elements = realloc(UI_Elements, ElementCount * sizeof(struct UI_Element));
            malloc_verify(UI_Elements);
    for (int i = startIndex; i < ElementCount; i++)
        UI_Elements[i] = elementlist[i - startIndex];
}