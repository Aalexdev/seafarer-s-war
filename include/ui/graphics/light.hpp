#ifndef __LIGHT__
#define __LIGHT__

    void light(int power, int x, int y, int r, int g, int b);
    
    /**
     * @brief render a projected light
     * 
     * @param angle the angleof the light
     * @param range the range of the light (angle + (range/2))
     * @param x the starting x
     * @param y the starting y
     * @param r the red color
     * @param g the green color
     * @param b the blue color
     */
    void projectedLight(int angle, int range, int x, int y, int r, int g, int b, int a, int radius);   

#endif