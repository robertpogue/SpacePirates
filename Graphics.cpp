#include "Graphics.h"
#include "Color.h"
#include "Point.h"
#ifdef _WIN32
    #include "SDL.h"
    #include "SDL_opengl.h"
    #include "SDL_ttf.h"
#else
    #include "SDL/SDL.h"
    #include "SDL/SDL_opengl.h"
    #include "SDL/SDL_ttf.h"
#endif
#include <stdexcept>

// file-scope variables
static SDL_Surface* screen = NULL;
static SDL_Color textColor = {255,255,255};
static SDL_Surface* textSurface = NULL;
static TTF_Font* font = NULL;

void Graphics::startUp() {
    const int screenWidth = 1024;
    const int screenHeight = 768;
    const int screenBPP = 32;
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(screenWidth,
                              screenHeight,
                              screenBPP,
                              SDL_OPENGL);

    // initialize ttf font graphics
    TTF_Init();
    static int fontSize = 14; // pt
    font = TTF_OpenFont("VeraMono.ttf", fontSize);
    if(font == NULL) throw std::runtime_error("failed to load font");

    // initialize openGL
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, screenWidth, 0.0, screenHeight, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(darkBlue.rNorm(), darkBlue.gNorm(), darkBlue.bNorm(), 1);
    SDL_WM_SetCaption("Space Pirates", NULL);
}

void Graphics::writeText(std::string text, int xPos, int yPos) {
    /*textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Rect offset;
    offset.x = xPos;
    offset.y = yPos;
    Uint8 pixelByteDepth = textSurface->format->BytesPerPixel;
    GLenum textureFormat;
    // alpha
    if(pixelByteDepth == 4) {
        if(textSurface->format->Rmask == 0x000000FF) {
            textureFormat = GL_RGBA;
        }
        else {
            textureFormat = GL_BGRA;
        }
    }
    else {
        if(textSurface->format->Rmask == 0x000000FF) {
            textureFormat = GL_RGB;
        }
        else {
            textureFormat = GL_BGR;
        }
    }
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, pixelByteDepth, textSurface->w, textSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, textSurface->pixels);
    glBindTexture(GL_TEXTURE_2D, texture);*/
}

void Graphics::flip() {
    SDL_GL_SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::triangle(const Point& p1, const Point& p2, const Point& p3, const Color& c) {
    glBegin(GL_TRIANGLES);
        glColor3f( c.r/255.f, c.g/255.f, c.b/255.f );
        glVertex2f((GLfloat)p1.x, (GLfloat)p1.y);
        glVertex2f((GLfloat)p2.x, (GLfloat)p2.y);
        glVertex2f((GLfloat)p3.x, (GLfloat)p3.y);
    glEnd();
}

void Graphics::shutDown() {
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(screen);
    SDL_Quit();
}
