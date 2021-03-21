#include "ui/graphics/light.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include "main.hpp"

void light(int power, int x, int y, int r, int g, int b){
    for (int i=0; i<power; i+=5){
        if (i > power / 3){
            filledCircleRGBA(RENDERER, x, y, i, r, g, b, 10);
        }
    }
}

void projectedLight(int angle, int range, int x, int y, int r, int g, int b, int a, int radius){
    
    for (int i=0; i<range/2; i++){
        int rx, ry;
        setAngleM(&rx, &ry, radius, i+angle+(range/2));
        int lx, ly;
        setAngleM(&lx, &ly, radius, i+angle-(range));
        
        filledTrigonRGBA(RENDERER, x, y, rx+x, ry+y, lx+x, ly+y, r, g, b, a);
    }
    
}