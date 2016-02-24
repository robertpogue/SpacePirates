#include "Graphics.h"
#include "Color.h"
#include "Point.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <stdexcept>

// file-scope variables
static SDL_Window* window = NULL;

void Graphics::startUp() {
    const int screenWidth = 1024;
    const int screenHeight = 768;
    const int screenBPP = 32;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SpacePirates",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth,
                              screenHeight,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

/*
// TODO: not sure if we want to use opengl
    // initialize openGL
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, screenWidth, 0.0, screenHeight, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(darkBlue.rNorm(), darkBlue.gNorm(), darkBlue.bNorm(), 1);
    SDL_WM_SetCaption("Space Pirates", NULL);
    */
}

void Graphics::flip() {
    SDL_UpdateWindowSurface(window);
}

void Graphics::triangle(const Point& p1, const Point& p2, const Point& p3, const Color& c) {
    /*
    glBegin(GL_TRIANGLES);
        glColor3f( c.r/255.f, c.g/255.f, c.b/255.f );
        glVertex2f((GLfloat)p1.x, (GLfloat)p1.y);
        glVertex2f((GLfloat)p2.x, (GLfloat)p2.y);
        glVertex2f((GLfloat)p3.x, (GLfloat)p3.y);
    glEnd();
    */
}

void Graphics::shutDown() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
