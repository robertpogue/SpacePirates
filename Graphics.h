#pragma once
#include <string>
#include <memory>

#include "Point.h"
#include "Ship.h"

// forward declare
class Image;
struct SDL_Window;
struct SDL_Renderer;
struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

class Graphics {
public:
    Graphics();
    ~Graphics();
    void    clear();
    Image   load(std::string);
    int     getHeight() const; // px
    // will place bottom left of texture at destination point
    // destination is in pixels from bottom left of screen
    void    draw(Point);
    void    draw(Ship);
    void    draw(Image);
    void    draw(std::string text, Point destination);
    void    present();
    static const int screenWidth = 1000;
    static const int screenHeight = 700;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    // utility functions
    void toSDLCoordinates(Point& p) const; // modifies p
    void blit(const Image&, Point destination, float rotation = 0);
};
