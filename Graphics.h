#pragma once
#include <string>

#include "SDL.h"
#include "Texture.h"
#include "Point.h"

class Graphics {
public:
    Graphics();
    ~Graphics();
    Texture load(std::string path);
    void    clear();
    int     getHeight(); // px
    // will place center of texture at destination point
    // destination is in pixels from bottom left of screen
    void blit(const Texture&, Point destination, float rotation);
    void present();
    void writeText(std::string text, Point destination);
private:
    SDL_Window* window;
    SDL_Renderer* renderer; //TODO raii
};
