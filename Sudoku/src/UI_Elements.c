#include "UI_Elements.h"

struct UI_TextureElement *TitleScreen;
struct UI_TextureElement *Title;
void UIElements_Init(){
    TitleScreen = malloc(sizeof(UI_TextureElement));
    SetErrorIndentfyer("UI_Elements: GENS_TitleScreen"); malloc_verify(TitleScreen);
    GC_Append(TitleScreen);

    Title = malloc(sizeof(UI_TextureElement));
    SetErrorIndentfyer("UI_Elements: GENS_Title"); malloc_verify(Title);
    GC_Append(Title);
}


void UIElements_GenerateStatic(){
    #pragma region TitleScreen
    SDL_Color TS_fg = {0, 0, 0, 255};
    int TS_w, TS_h;
    TitleScreen->texture = RenderFont(MainRenderer, GetFont(), TITLE_SCREEN, TS_fg, &TS_w, &TS_h);
    SDL_Rect TS_rect;
        TS_rect.w = (int)SDL_round(MainWindowWidth * 0.4);
        TS_rect.h = (int)SDL_round(((double)TS_rect.w / TS_w) * TS_h);
        TS_rect.x = (int)SDL_round((MainWindowWidth / 2.0) - (TS_rect.w / 2));
        TS_rect.y = (int)SDL_round((MainWindowHeight / 2.0) - (TS_rect.h / 2));
    TitleScreen->rect = TS_rect;
    #pragma endregion

    #pragma region Title
    SDL_Color Title_fg = {102, 255, 0, 250};
    int Tile_w, Title_h;
    Title->texture = RenderFont(MainRenderer, GetFont(), TITLE_SCREEN, Title_fg, &Tile_w, &Title_h);
    SDL_Rect Title_rect;
        Title_rect.w = (int)SDL_round(MainWindowWidth * 0.3);
        Title_rect.h = (int)SDL_round(((double)Title_rect.w / Tile_w) * Title_h);
        Title_rect.x = (int)SDL_round((MainWindowWidth / 2.0) - (Title_rect.w / 2));
        Title_rect.y = (int)SDL_round((MainWindowHeight * 0.03));
    Title->rect = Title_rect;
    #pragma endregion
}

