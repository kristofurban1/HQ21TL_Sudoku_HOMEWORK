#include "UI_Elements.h"

struct UI_TextureElement *TitleScreen;

void UIElements_GenerateStatic(){
    #pragma region TitleScreen
    SDL_Color TS_fg = {255, 255, 255, 255};
    TitleScreen = malloc(sizeof(UI_TextureElement));
    SetErrorIndentfyer("UI_Elements: GENS_TitleScreen"); malloc_verify(TitleScreen);
    int TS_w, TS_h;
    TitleScreen->texture = RenderFont(MainRenderer, GetFont(), TITLE_SCREEN, TS_fg, &TS_w, &TS_h);
    SDL_Rect rect;
        rect.w = (int)SDL_round(MainWindowWidth * 0.7);
        rect.h = (int)SDL_round(((double)TS_w / rect.w) * TS_h);
        rect.x = (int)SDL_round((MainWindowWidth / 2.0) - (rect.w / 2));
        rect.y = (int)SDL_round((MainWindowHeight / 2.0) - (rect.h / 2));
    TitleScreen->rect = rect;
    GC_Append(TitleScreen);
    #pragma endregion

    

}