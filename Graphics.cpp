#include "Graphics.h"
#include <assert.h>
#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Image.h"

// file-scope variables
static SDL_Window* window = NULL;

Graphics::Graphics() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    assert(result == 0);
    result = TTF_Init();
    assert(result == 0);

    window = SDL_CreateWindow("Space Pirates", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    assert(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(renderer);
}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Image Graphics::load(std::string path) {
    return Image(path, renderer);
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

int Graphics::getHeight() const {
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    return h;
}

void Graphics::blit(const Image& texture, Point destination, float rotation) {
    // convert from Graphics coordinate system (origin at bottom left)
    // to SDL coordinate system (origin at top left)
    toSDLCoordinates(destination);
    rotation = -rotation * (180.0f / 3.14159f); // convert from radians to pi
    SDL_Rect dest;
    dest.x = (int)destination.x;
    dest.y = (int)destination.y;

    // sdl positions the texture's top left corner at dest
    // we would like to position the texture's center at dest.
    // subtract half width and half height
    dest.x -= texture.getWidth()/2;
    dest.y -= texture.getHeight()/2;

    dest.w = texture.getWidth(); // maintain texture size
    dest.h = texture.getHeight();
    

    SDL_RenderCopyEx(renderer,
                     texture.sdlTexture(), // source
                     nullptr,              // source rectangle
                     &dest,                // destination rectangle
                     rotation,             // angle in degrees
                     nullptr,              // center of rotation, default to h/2, w/2
                     SDL_FLIP_NONE );
}

void Graphics::draw(Point p) {
    toSDLCoordinates(p);
    SDL_RenderDrawPoint(renderer, (int)p.x, (int)p.y);
}

void Graphics::draw(Ship ship) {
    blit(ship.getImage(), ship.getPosition(), ship.getRotation());
    draw(ship.getPosition());
}

void Graphics::draw(std::string text, Point destination) {
    int fontsize = 12;
    SDL_Color color{ 50, 50, 50, 200 }; // rgba
                                        //TODO RAII and cache font
    TTF_Font* font = TTF_OpenFont("DejaVuSans-ExtraLight.ttf", 12);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    Image textImage(surface, texture);
    blit(textImage, destination, 0);
    TTF_CloseFont(font);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::toSDLCoordinates(Point& p) const {
    p.y = -p.y + getHeight();
}