#include "Image.h"
#include <algorithm>    // std::min
#include <assert.h>
#include "SDL.h"

#include "Graphics.h"


Image::Image() : texture(nullptr), surface(nullptr) {}

Image::Image(std::string path, SDL_Renderer* renderer)
: texture(nullptr), surface(nullptr) {
    //TODO fix
    SDL_Surface* s = SDL_LoadBMP(path.c_str());
    surface = std::shared_ptr<SDL_Surface>(s, SDL_FreeSurface);
    // set key color (treated as transparent)
    Uint32 colorKey = SDL_MapRGB(s->format, 255, 0, 255);
    SDL_SetColorKey(s, SDL_TRUE, colorKey);

    SDL_Texture* t = SDL_CreateTextureFromSurface(
        renderer, surface.get());
    texture = std::shared_ptr<SDL_Texture>(t, SDL_DestroyTexture);
}

Image::Image(SDL_Surface* s, SDL_Texture* t) {
    surface = std::shared_ptr<SDL_Surface>(s, SDL_FreeSurface);
    texture = std::shared_ptr<SDL_Texture>(t, SDL_DestroyTexture);
}

SDL_Texture* Image::sdlTexture() const {
    return texture.get();
}

Color Image::getPixel(Point p) {
    // sdl has origin at top left, +y down
    // spacepirates considers origin to to be center +y up
    //p.y = -p.y + getHeight();
    //p.x += getWidth() / 2.f;
    //p.y += getHeight() / 2.f;

    int x = (int)round(p.x); // nearest pixel
    int y = (int)round(p.y);

    // clamp to range (0,0) to (width, height)
    x = std::min(x, getWidth());
    x = std::max(x, 0);
    y = std::min(y, getHeight());
    y = std::max(y, 0);
    Uint32* pixels = (Uint32*)surface->pixels;
    Uint8 r, g, b, a;
    SDL_GetRGBA(pixels[(y*surface->w) + x], surface->format, &r, &g, &b, &a);
    return Color(r, g, b); // TODO add alpha chanel

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