#include "FontManager.h"

TTF_Font *__FONT__;

TTF_Font *LoadFont(int size){
    TTF_Font *font = TTF_OpenFont(GetAsset(ASSET_FONT), size);
    SetErrorIndentfyer("FontManager: TTF_FontLoad");
    SDL_ptr_verify(font);
    return font;
}

SDL_Texture *RenderFont(SDL_Renderer *renderer, TTF_Font *font, char *text, SDL_Color fg, int *width, int *height){
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, fg);
    SetErrorIndentfyer("FontManager: TTF_Rendertext"); SDL_ptr_verify(surface);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SetErrorIndentfyer("FontManager: TTF_Texture<Surface"); SDL_ptr_verify(texture);
    free(surface);

    SDL_QueryTexture(texture, NULL, NULL, width, height);
    return texture;
}

void FontManager_Init(){
    __FONT__ = LoadFont(FontSize); GC_Append(__FONT__);
}

TTF_Font *GetFont(){ return __FONT__; }