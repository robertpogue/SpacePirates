#include "Texture.h"

Texture::Texture(SDL_Texture* t)
    : texture(t, SDL_DestroyTexture) {} // custom deleter RAII


SDL_Texture* Texture::sdlTexture() const {
    return texture.get();
}

int Texture::getWidth() const {
    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
    return w;
}
int Texture::getHeight() const {
    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
    return h;
}