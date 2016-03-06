#pragma once
#include <string>

#include "SDL.h"
#include "Point.h"
#include "Ship.h"

class Image;

class Graphics {
public:
    Graphics();
    ~Graphics();
    void    clear();
    int     getHeight() const; // px
    // will place bottom left of texture at destination point
    // destination is in pixels from bottom left of screen
    void    blit(const Image&, Point destination, float rotation);
    void    draw(Point);
    void    draw(Ship);
    void    draw(std::string text, Point destination);
    void    present();
    static const int screenWidth = 1000;
    static const int screenHeight = 700;
    SDL_Renderer* renderer;
private:
    SDL_Window* window;
    

    // utility functions
    void toSDLCoordinates(Point& p) const; // modifies p
};
