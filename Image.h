#pragma once

#include "Color.h"
#ifdef _WIN32
	#include "SDL.h"
#else
	#include "SDL/SDL.h"
#endif
#include <memory>
#include <string>

class Image {
	std::shared_ptr<SDL_Surface> imageData;
public:
	void load(std::string path);
	Color getPixel(int x, int y);
	int width() { return imageData->w; }
	int height() { return imageData->h; }
};

void surfaceDeleter(SDL_Surface* s);
