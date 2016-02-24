#include "Image.h"
#include "Color.h"
#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

void Image::load(std::string path) {
    /*
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if(tempSurface == NULL) {
        throw std::runtime_error("error loading image: " + path);
    }
	SDL_Surface* optimizedSurface = SDL_DisplayFormat(tempSurface);
	surfaceDeleter(tempSurface);
	imageData = std::shared_ptr<SDL_Surface>(optimizedSurface, surfaceDeleter);
	SDL_LockSurface(imageData.get());
  */
}

Color Image::getPixel(int x, int y) {
	// ensure image is 8 bit in depth
	SDL_PixelFormat *fmt = 0;
	fmt = imageData->format;
	if(fmt->BitsPerPixel != 32) throw std::runtime_error("wrong pixel format");
	// lock surface to get pixel
	Uint32* pixels = (Uint32*)imageData->pixels;
	Uint32 pixel = pixels[(y * imageData->w) + x];
	Uint8 red, green, blue;
	SDL_GetRGB(pixel, imageData->format, &red, &green, &blue);
	return Color(red, green, blue);
}

void surfaceDeleter(SDL_Surface* surface) {
	SDL_FreeSurface(surface);
}
