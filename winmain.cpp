#include <SDL.h>
#include <exception>
#include <string>

int main(int argc, char ** argv) {
    try {
        if(SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw  std::exception(SDL_GetError());
        }

        SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
        if(win == nullptr) {
            throw  std::exception("SDL_CreateWindow Error");
        }
        SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(ren == nullptr) {
            SDL_DestroyWindow(win);
            throw std::exception("SDL_CreateRenderer Error");
        }

        std::string imagePath = "hello.bmp";
        SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
        if(bmp == nullptr) {
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(win);
            throw std::exception("SDL_LoadBMP Error: ");
        }

        SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
        SDL_FreeSurface(bmp);
        if(tex == nullptr) {
            //UTOH
        }

        //A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
        for(int i = 0; i < 3; ++i) {
            //First clear the renderer
            SDL_RenderClear(ren);
            //Draw the texture
            SDL_RenderCopy(ren, tex, NULL, NULL);
            //Update the screen
            SDL_RenderPresent(ren);
            //Take a quick break after all that hard work
            SDL_Delay(1000);
        }

        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        SDL_Quit(); //TODO raii
        return 0;
    } catch(std::exception) {
        return 1;
    }



}