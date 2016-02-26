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
    // point is in pixels from top left of screen
    void blit(const Texture&, Point destination, float rotation);
    void present();
    //void triangle(const Point& p1, 
        //const Point& p2,
        //const Point& p3,
        //const Color& c);
    //void writeText(std::string text, int xPos, int yPos);
    //void flip();
private:
    SDL_Window* window;
    SDL_Renderer* renderer; //TODO raii
};
