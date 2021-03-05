/*
 * text.hpp by Aalex
 * 
 * content:
 *  Text class from Widget
*/

#ifndef __TEXT__
#define __TEXT__

    #include <iostream>
    #include <cstring>
    #include <SDL2/SDL.h>
    
    using namespace std;

    #include "api/io/xml.hpp"

    class Text{
        public:
            Text();
            ~Text();

            bool setText(string new_text);
            string getText(void);

            bool draw(void);

            void setColor(Uint8 r, Uint8 g, Uint8 b);
            bool setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
            void setColor(SDL_Color new_color);

            bool setAlpha(Uint8 a);
            Uint8 getAlpha(void);

            // rect
            SDL_Rect getRect(void){return this->rect;}
            void setRect(SDL_Rect new_rect){this->rect = new_rect;}

            void setSize(int w, int h);
            void getSize(int *w, int *h);

            void setPos(int x, int y);
            void getPos(int *x, int *y);

            int getX(void){return this->rect.x;}
            int getY(void){return this->rect.y;}
            int getW(void){return this->rect.w;}
            int getH(void){return this->rect.h;}

            void setX(int x){this->rect.x = x;}
            void setY(int y){this->rect.y = y;}
            void setW(int w){this->rect.w = w;}
            void setH(int h){this->rect.h = h;}

            bool read_from_xml(XMLNode* node);
        
        private:
            string text;
            SDL_Texture* texture;
            SDL_Rect rect;
            SDL_Color color;
    };

#endif