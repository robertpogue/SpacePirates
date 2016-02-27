#include "Graphics.h"
#include <assert.h>
#include "SDL_ttf.h"

// file-scope variables
static SDL_Window* window = NULL;

Graphics::Graphics() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    assert(result == 0);
    result = TTF_Init();
    assert(result == 0);

    window = SDL_CreateWindow("Space Pirates", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    assert(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(renderer);
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Texture Graphics::load(std::string path) {
    SDL_Surface* bmp = SDL_LoadBMP(path.c_str());
    assert(bmp);

    Texture t(SDL_CreateTextureFromSurface(renderer, bmp));
    SDL_FreeSurface(bmp);

    return t;
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

int Graphics::getHeight() {
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    return h;
}

void Graphics::blit(const Texture& texture, Point destination, float rotation) {
    // convert from Graphics coordinate system (origin at bottom left)
    // to SDL coordinate system (origin at top left)
    destination.y = -destination.y + getHeight();
    rotation = -rotation * (180.0f / 3.14159f); // convert from radians to pi
    SDL_Rect dest;
    dest.x = (int)destination.x;
    dest.y = (int)destination.y;
    dest.w = texture.getWidth();
    dest.h = texture.getHeight();;
    

    SDL_RenderCopyEx(renderer,
                     texture.sdlTexture(), // source
                     nullptr,              // source rectangle
                     &dest,                // destination rectangle
                     rotation,             // angle in degrees
                     nullptr,              // center of rotation, default to h/2, w/2
                     SDL_FLIP_NONE );
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::writeText(std::string text, Point destination) {
    int fontsize = 12;
    SDL_Color color{ 200, 200, 200, 200 }; // rgba
    //TODO RAII
    TTF_Font* font = TTF_OpenFont("DejaVuSans-ExtraLight.ttf", 12);
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    blit(texture, destination, 0);
    TTF_CloseFont(font);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}