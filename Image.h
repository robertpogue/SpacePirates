#pragma once
#include <memory>
#include <string>

#include "SDL.h"
#include "Color.h"
#include "Point.h"

// forward declare
class Graphics;

class Image {
public:
    Image();
    Image(std::string path, Graphics&);
    Image(SDL_Surface*, SDL_Texture*); // takes ownership - will free
    SDL_Texture* sdlTexture() const; // do NOT keep a copy of this pointer
	Color        getPixel(Point p);
    int          getWidth() const;
    int          getHeight() const;

private:
    // smart pointer with custom deleter
    std::shared_ptr<SDL_Surface> surface;
    std::shared_ptr<SDL_Texture> texture;
    
};
