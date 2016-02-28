#include "Image.h"
#include <assert.h>
#include "Graphics.h"

Image::Image() : texture(nullptr), surface(nullptr) {}

Image::Image(std::string path, Graphics& g) {
    SDL_Surface* s = SDL_LoadBMP(path.c_str());
    surface = std::shared_ptr<SDL_Surface>(s, SDL_FreeSurface);
    // set key color (treated as transparent)
    Uint32 colorKey = SDL_MapRGB(s->format, 255, 0, 255);
    SDL_SetColorKey(s, SDL_TRUE, colorKey);

    SDL_Texture* t = SDL_CreateTextureFromSurface(
        g.renderer, surface.get());
    texture = std::shared_ptr<SDL_Texture>(t, SDL_DestroyTexture);
}

Image::Image(SDL_Surface* s, SDL_Texture* t) {
    surface = std::shared_ptr<SDL_Surface>(s, SDL_FreeSurface);
    texture = std::shared_ptr<SDL_Texture>(t, SDL_DestroyTexture);
}

SDL_Texture* Image::sdlTexture() const {
    return texture.get();
}

int Image::getWidth() const {
    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
    return w;
}
int Image::getHeight() const {
    int w, h;
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h);
    return h;
}