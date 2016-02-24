#include "Texture.h"

Texture::Texture(SDL_Texture* t)
    : texture(t, textureDeleter) {}


SDL_Texture* Texture::sdlTexture() const {
    return texture.get();
}

void textureDeleter(SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
}
