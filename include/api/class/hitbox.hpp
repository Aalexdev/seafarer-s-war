#ifndef __HITBOX__
#define __HITBOX__

    #include "api/functions/math.hpp"
    #include "api/io/xml.hpp"
    #include <vector>

    class HitPoint{

        public:
            HitPoint(){}
            ~HitPoint(){}

            int x, y;
            int angle, distFromCenter;

            void calculate(Point *center, int &angle);
    };

    class Hitbox{
        public:
            Hitbox();
            ~Hitbox();

            // will create a hitBox from a hitbox xml Node
            bool read_from_xml(XMLNode* node);
            
            // push the hitPoint add the back of the HitBox
            void push(HitPoint *pnt);

            // delete the last point of the HitBox
            void pop(void);

            // set the angle of the hitbox
            void setAngle(int new_angle);

            // return the angle of the Hitbox
            int getAngle(void){return this->angle;}

            // set the position of the Hitbox
            void setPos(Point new_pos);

            // return the rect of the Hitbox
            SDL_Rect getRect(void){return this->rect;}

            // reset the rect with points
            void reload_rect(void);

            // draw the hitBox
            bool draw(void);

            // set the draw Color, init as 255,0,0
            void setDrawColor(SDL_Color new_color);

            // retrun true if the point is inside the hitBox
            bool is_point_inside(Point point);

            // retrun true is the hitbox is inside this
            bool is_collide(Hitbox *hitbox);

            // clear all points
            void clear(void);

            // get center
            Point getCenter(void){return this->center;}

        private:

            // points of the hitbox
            vector<HitPoint*> hitPoints;

            int angle;
            Point center;
            SDL_Rect rect;
            SDL_Color color;
    };

#endif