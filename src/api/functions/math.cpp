#include "api/functions/math.hpp"

int hexa_to_int(char value){

    switch (value){
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
        case 'g':
            return 16;
        default:
            return 0;
    }
}

bool pointInRect(Point pnt, SDL_Rect rect){
    if (pnt.x >= rect.x && pnt.x <= rect.x + rect.w){
        if (pnt.y >= rect.y && pnt.y <= rect.y + rect.h){
            return true;
        }
    }
    return false;
}

int max(int a, int b){
    return a > b ? a : b;
}

int min(int a, int b){
    return a < b ? a : b;
}

int getDistanceM(int x1, int y1, int x2, int y2){
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int getAngleM(int x1, int y1, int x2, int y2){
    return atan2((x1 - x2), (y1 - y2)) * 180 / M_PI;
}

bool onSegment(Point p, Point q, Point r) { 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 

int orientation(Point p, Point q, Point r) { 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}
bool doIntersect(Point p1, Point q1, Point p2, Point q2) { 

    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    if (o1 != o2 && o3 != o4) 
        return true; 

    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false;
} 

bool isInside(Point polygon[], int n, Point p) { 
    if (n < 3)  return false; 
    Point extreme = {INF, p.y}; 
  
    int count = 0, i = 0; 
    do { 
        int next = (i+1)%n; 

        if (doIntersect(polygon[i], polygon[next], p, extreme)) { 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
               return onSegment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    return count&1;
}


void setAngleM(int *X, int *Y, float distFromCenter, float angle){
    *X = cos(angle*M_PI/180) * distFromCenter;
    *Y = sin(angle*M_PI/180) * distFromCenter;
}