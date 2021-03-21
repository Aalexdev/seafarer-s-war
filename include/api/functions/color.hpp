#ifndef __COLOR__
#define __COLOR__

    #include "main.hpp"

    /**
     * @brief create a SDL_Color from color value
     * 
     * @param r red canal
     * @param g green canal
     * @param b blue canal
     * @return return a SDL_Color
     */
    SDL_Color color(Uint8 r, Uint8 g, Uint8 b);

    /**
     * @brief create a SDL_Color from color value
     * 
     * @param r red canal
     * @param g green canal
     * @param b blue canal
     * @param a alpha canal
     * @return return a SDL_Color
     */
    SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     * @brief load a color from a string hexadecimal value (RGBA)
     * 
     * @param color hexadecimal
     * @return return the color loaded from the string
     */
    SDL_Color HEXA_to_color(string color);

    /**
     * @brief load a color from a string hexadecimal value (RGB)
     * 
     * @param color hexadecimal
     * @return return the color loaded from the string
     */
    SDL_Color RGB_To_color(string color);

#endif