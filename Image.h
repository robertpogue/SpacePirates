#pragma once
#include <memory>
#include <string>

#include "Color.h"
#include "Point.h"

// forward declare
class Graphics;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Image {
public:
    Image();
    Image(std::string path, SDL_Renderer*);
    Image(SDL_Surface*, SDL_Texture*); // takes ownership - will free
	Color        getPixel(Point p);    // origin at bottom left, +x to right, +y up
    Color        getPixel(int x, int y);
    int          getWidth() const;
    int          getHeight() const;

    SDL_Texture* sdlTexture() const;   // do NOT keep a copy of this pointer
private:
    // smart pointer with custom deleter
    std::shared_ptr<SDL_Surface> surface;
    std::shared_ptr<SDL_Texture> texture;
    
};
