#ifndef __COLOR__
#define __COLOR__

    #include "main.hpp"

    SDL_Color color(Uint8 r, Uint8 g, Uint8 b);
    SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    SDL_Color HEXA_to_color(string color);
    SDL_Color RGB_To_color(string color);

#endif