#include "Interface.h"

int CurrentTriggerAreaID;

void Interface_InitCurrentState(){
    CurrentTriggerAreaID = -1;
    switch (GetGamestate())
    {
    case GS_MainMenu:
        struct UI_Element *startbutton = UI_GetByID(STARTBUTTON_UID);
        startbutton->TriggerCallback = &MM_Callback_StartButton_Pressed;
        break;
    
    case GS_SudokuState:
        struct UI_Element *backbutton = UI_GetByID(BACKBUTTON_UID);
        backbutton->TriggerCallback = &SI_Callback_BackButton_Pressed;
        break;
        
    default:
        break;
    }
}

void IF_HandleTriggered(struct UI_Element *triggered){
    triggered->trigger.isTriggered = true;
    triggered->trigger.trigger_stay_ms = 30;
    if (triggered->hasBackground) triggered->background->bgcolor = triggered->t_bgcolor;
    if (triggered->hasLabel) triggered->label.fgcolor = triggered->t_fgcolor;
    triggered->TriggerCallback(triggered->UniqueID);
}

void Interface_EventHandler_Keyboard(SDL_Scancode keypress){
    if (keypress != SDL_SCANCODE_UNKNOWN){
        if (keypress == SDL_SCANCODE_RETURN){
            printf("IF: Keypress: ENTER\n");
            int trig_count;
            struct UI_Element **triggered = UIs_GetByTAID(CurrentTriggerAreaID, &trig_count);
            for (int i = 0; i < trig_count; i++)
                IF_HandleTriggered(triggered[i]);
            
            TryFree(triggered);
        }
    }
}

void Interface_EventHandler_Mouse(SDL_Point cursorClick){
    if (cursorClick.x + cursorClick.y != -2){
        int uid = UI_SearchForTriggeredElement(cursorClick);
        printf("HIT_UID: %d\n", uid);
        if (uid == -1) return;
        struct UI_Element *triggered = UI_GetByID(uid);
        if (triggered == NULL) return;
        IF_HandleTriggered(triggered);
    }
}