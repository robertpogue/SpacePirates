#include "Image.h"
#include <algorithm>    // std::min
#include <assert.h>
#include "SDL.h"

#include "Graphics.h"


Image::Image() : texture(nullptr), surface(nullptr) {}

Image::Image(std::string path, SDL_Renderer* renderer)
: texture(nullptr), surface(nullptr) {
    surface = std::shared_ptr<SDL_Surface>(SDL_LoadBMP(path.c_str()), SDL_FreeSurface);
    // set key color (treated as transparent)
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 0, 255);
    SDL_SetColorKey(surface.get(), SDL_TRUE, colorKey);

    texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer, surface.get()),
        SDL_DestroyTexture);
}

Image::Image(SDL_Surface* s, SDL_Texture* t) {
    surface = std::shared_ptr<SDL_Surface>(s, SDL_FreeSurface);
    texture = std::shared_ptr<SDL_Texture>(t, SDL_DestroyTexture);
}

SDL_Texture* Image::sdlTexture() const {
    return texture.get();
}

Color Image::getPixel(Point p) {
    // sdl has origin at top left, +x right, +y down
    // convert to sdl coordinates
    p.y = -p.y + getHeight();
    //p.x += getWidth() / 2.f;
    //p.y += getHeight() / 2.f;

    // round to nearest pixel
    int x = (int)round(p.x);
    int y = (int)round(p.y);

    // clamp to range (0,0) to (width, height)
    x = std::min(x, getWidth());
    x = std::max(x, 0);
    y = std::min(y, getHeight());
    y = std::max(y, 0);

    // check for expected pixel format
    assert(surface->format->BytesPerPixel == 2);
    assert(SDL_MUSTLOCK(surface) == false);
    Uint16* pixels = (Uint16*)surface.get()->pixels;
    Uint8 r, g, b;
    Uint16 pixel = pixels[(y*surface->w) + x];
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);
    return Color(r, g, b); // FUTURE add alpha chanel

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