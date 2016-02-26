#include "Texture.h"

Texture::Texture(SDL_Texture* t)
    : texture(t, SDL_DestroyTexture) {} // custom deleter RAII all the way!


SDL_Texture* Texture::sdlTexture() const {
    return texture.get();
}