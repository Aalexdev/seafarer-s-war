#include "ui/main_window.hpp"
#include "main.hpp"

bool resteWindow(const char* title, int Xpos, int Ypos, int width, int height, int flags){
    if (IS_LOG_OPEN) LOG << "resetWindow(" << title << ", " << Xpos << ", " << Ypos << ", " << width << ", " << height << ", " << flags << ")" << endl;
    clearWindow();

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        MAINVAR->window = SDL_CreateWindow(title, Xpos, Ypos, width, height, flags);
        if (MAINVAR->window){  
            MAINVAR->renderer = SDL_CreateRenderer(MAINVAR->window, -1, 0);
            if (MAINVAR->renderer){
                SDL_SetRenderDrawColor(MAINVAR->renderer,  0, 0, 0, 255);
                MAINVAR->isInit = true;
                SDL_RenderPresent(RENDERER);
            } else {
                cerr << "SDL_CreateRenderer error : " << SDL_GetError() << endl;
                return false;
            }
        } else {
            cerr << "SDL_CreatWindow error : " << SDL_GetError() << endl;
            return false;
        }
    } else {
        cerr << "SDL_Init error : " << SDL_GetError() << endl;
        return false;
    }

    return true;        
}

void clearWindow(void){
    if (IS_LOG_OPEN) LOG << "clearWindow" << endl;

    if (WINDOW){
        SDL_DestroyWindow(WINDOW);
        WINDOW = nullptr;
    }

    if (RENDERER){
        SDL_DestroyRenderer(RENDERER);
        RENDERER = nullptr;
    }

    if (ISINIT){
        SDL_Quit();
        ISINIT = false;
    }
}