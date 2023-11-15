#ifndef UIElements_DEF
#define UIElements_DEF

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define M_PI		3.14159265358979323846

#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "Cleanup.h"
#include "FontManager.h"
#include "animation_handler.h"
#include "GameState.h"
#include "debugmalloc.h"
#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#define STARTBUTTON_UID 11
#define BACKBUTTON_UID 21

extern int ElementCount;
extern struct UI_Element **UI_Elements;

extern struct UI_Pos{
    int width, height, x, y;
} UI_Pos;

extern struct Shape{
    int offset_X, offset_Y;
    int height;
    int width;
    int *boundrary_start;
    int *boundrary_end;
} Shape;

extern struct UI_ElementShape{
    struct Shape **shapes; 
    int shapeCount;
    bool visible;
    SDL_Color bgcolor;
} UI_ElementShape;

extern struct UI_Trigger{
    int TriggerAreaID;
    struct UI_ElementShape *area;
    bool isTriggered;
    bool enabled;
    int trigger_stay_ms;
} UI_Trigger;

extern struct UI_Label{
    char *text;
    SDL_Rect rect;
    SDL_Texture *texture;
    bool makeFit;
    bool preferWidthOverHeight;
    int targetSize_W, targetSize_H;
    int offset_X, offset_Y;
    SDL_Color fgcolor;
    bool visible;
} UI_Label;

extern struct UI_Element{
    int UniqueID;
    struct UI_Pos pos;
    SDL_Color bgcolor;
    SDL_Color t_bgcolor;
    bool hasBackground;
    struct UI_ElementShape *background;
    bool hasLabel;
    SDL_Color fgcolor;
    SDL_Color t_fgcolor;
    struct UI_Label label;
    bool hasAnim;
    struct Animation anim;
    bool hasTrigger;
    struct UI_Trigger trigger;
    void (* TriggerCallback) (int); // int: Sender_UID
    bool visible;
} UI_Element;

extern void ResetElements();

extern struct UI_Element *UI_GetByID(int uniqueID);
extern struct UI_Element **UIs_GetByTAID(int triggerAreaID, int *match_count);
extern bool InTriggerAreaOfElement(struct UI_Element *element, SDL_Point point);
extern int UI_SearchForTriggeredElement(SDL_Point cursorpos);

extern void UIElements_Generate();

extern void UpdateElementLabelText(struct UI_Element *element, char *newText);

#endif