#pragma once

#include "Color.h"
#include "SDL.h"
#include <memory>
#include <string>

class Texture {
public:
    Texture(SDL_Texture*);
    SDL_Texture* sdlTexture() const; // do NOT keep a copy of this pointer
	//void load(std::string path);
	//Color getPixel(int x, int y);
	//int width() { return imageData->w; }
	//int height() { return imageData->h; }

private:
    //std::shared_ptr<SDL_Surface> imageData;
    // unique_ptr with custom deleter
    std::shared_ptr<SDL_Texture> texture;
};
