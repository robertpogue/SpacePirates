#pragma once
#include <memory>
#include <string>

#include "Color.h"
#include "SDL.h"

// forward declare
class Graphics;

class Image {
public:
    Image();
    Image(std::string path, Graphics&);
    Image(SDL_Surface*, SDL_Texture*); // takes ownership - will free
    SDL_Texture* sdlTexture() const; // do NOT keep a copy of this pointer
	//void load(std::string path);
	//Color getPixel(int x, int y);
    int getWidth() const;
    int getHeight() const;

private:
    // smart pointer with custom deleter
    std::shared_ptr<SDL_Surface> surface;
    std::shared_ptr<SDL_Texture> texture;
    
};
