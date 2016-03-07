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

    int fontSize = 12;
    font = TTF_OpenFont("DejaVuSans-ExtraLight.ttf", fontSize);

}

Graphics::~Graphics() {
    TTF_CloseFont(font);
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

void Graphics::draw(Point p) {
    toSDLCoordinates(p);
    SDL_RenderDrawPoint(renderer, (int)p.x, (int)p.y);
}

void Graphics::draw(Ship ship) {
    Point position = ship.getPosition();
    // adjust for center of mass
    position = position - ship.getCenterOfMass();
    blit(ship.getImage(), position, ship.getRotation());

    // debug position
    draw(ship.getPosition());
}

void Graphics::draw(Image i) {
    blit(i, Point(0,0));
}

void Graphics::draw(std::string text, Point destination) {
    SDL_Color color{ 50, 50, 50, 200 }; // rgba
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    Image textImage(surface, texture);
    blit(textImage, destination, 0);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

void Graphics::toSDLCoordinates(Point& p) const {
    p.y = -p.y + getHeight();
}

void Graphics::blit(const Image& texture, Point destination, float rotation) {
    // convert from Graphics coordinate system (origin at bottom left)
    // to SDL coordinate system (origin at top left)
    toSDLCoordinates(destination);

    // move texture origin from top left to bottom left
    destination.y -= texture.getHeight();
    rotation = -rotation * (180.0f / 3.14159f); // convert from radians to pi

    SDL_Rect dest;
    dest.x = (int)destination.x;
    dest.y = (int)destination.y;

    dest.w = texture.getWidth(); // maintain texture size
    dest.h = texture.getHeight();

    SDL_RenderCopyEx(renderer,
        texture.sdlTexture(), // source
        nullptr,              // source rectangle
        &dest,                // destination rectangle
        rotation,             // angle in degrees
        nullptr,              // center of rotation, default to h/2, w/2
        SDL_FLIP_NONE);
}