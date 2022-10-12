#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* ren)
{
    SDL_Surface* temp = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, temp);

    SDL_FreeSurface(temp);

    return tex;
}
