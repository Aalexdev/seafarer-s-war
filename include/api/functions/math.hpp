#ifndef __MATH__
#define __MATH__

    #include <cmath>
    #include <SDL2/SDL.h>

    #define INF 100000

    int max(int a, int b);
    int min(int a, int b);

    struct Point{
        int x, y;
    };

    struct Line{
        Point sp;
        Point ep;
    };

    //return a the int value if th hexa input
    int hexa_to_int(char value);

    bool pointInRect(Point pnt, SDL_Rect rect);

    // return the distance (in px) beetwen this two points
    int getDistanceM(int x1, int y1, int x2, int y2);

    // return the angle form the point a to the point b
    int getAngleM(int x1, int y1, int x2, int y2);

    // set the x and the y from the distance for the center point and the angle
    void setAngleM(int *X, int *Y, float distFromCenter, float angle);

    // return true if the point is inside the polygon
    bool isInside(Point polygon[], int n, Point p);
    
    /**
     * @brief get if two lines intersect
     * 
     * @param p1 starting point of the fisrt line
     * @param q1 ending point of the fisrt line
     * @param p2 starting point of the second line
     * @param q2 ending point of the second line
     * @return return true if intersect, false if not
     */
    bool doIntersect(Point p1, Point q1, Point p2, Point q2);

#endif