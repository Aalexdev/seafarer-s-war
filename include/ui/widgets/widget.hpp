/*
 * widget.hpp by Aalex
 * 
 * content:
 *  Widget class
*/

#ifndef __WIDGET_H__
#define __WIDGET_H__
    
    #include <iostream>
    #include <cstring>
    #include <SDL2/SDL.h>

    #include "api/class/hitbox.hpp"
    #include "api/io/xml.hpp"

    using namespace std;

    class Widget{
        public:
            Widget();
            ~Widget();

            bool set_hitbox(Hitbox* new_hitbox);

            void add_hitPoint(int x, int y);
            void add_hitPoint(HitPoint* pnt);
            void add_hitPoint(Point p);

            void clear_hitbox(void);
            void pop_hitPoint(void);

            void draw_hitbox(void);

            bool is_mouse_inside(void);

        private:
            Hitbox* hitbox;
            SDL_Rect rect;
    };

#endif