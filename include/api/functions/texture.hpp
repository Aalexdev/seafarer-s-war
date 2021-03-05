#ifndef __TEXTURE__
#define __TEXTURE__

    #include <SDL2/SDL.h>
    #include <iostream>
    using namespace std;

    #include "api/io/xml.hpp"

    SDL_Texture* loadTexture(string path, SDL_Rect *rect);
    SDL_Texture* surfaceToTexture(SDL_Surface *surface, SDL_Rect *rect);
    SDL_Texture* createRGBTexture(SDL_Color color, SDL_Rect rect);

    class Image{
        public:
            Image(string path);
            Image(SDL_Color color);
            Image(Uint8 r, Uint8 g, Uint8 b);
            Image(){}

            ~Image();

            void setRect(SDL_Rect new_rect){this->rect = new_rect;}

            void setPos(int x, int y){this->rect.x = x; this->rect.y = y;}
            void setX(int x){this->rect.x;}
            void setY(int y){this->rect.y;}

            void setSize(int w, int h){this->rect.w; this->rect.h = h;}
            void setW(int w){this->rect.w = w;}
            void setH(int h){this->rect.h = h;}

            void getPos(int *x, int *y){x = &this->rect.x; y = &this->rect.y;}
            int getX(void){return this->rect.x;}
            int getY(void){return this->rect.y;}

            void getSize(int *w, int *h){w = &this->rect.w; h = &this->rect.h;}
            int getW(void){return this->rect.w;}
            int getH(void){return this->rect.h;}

            SDL_Rect* getRect(void) {return &this->rect;}

            bool set(string path);
            bool set(SDL_Color color);
            bool set(Uint8 r, Uint8 g, Uint8 b);
            bool setAlpha(Uint8 alpha);

            bool draw(void);

            bool read_from_xml(XMLNode* node);
        private:
            SDL_Rect rect;
            SDL_Texture* texture;
    };

#endif