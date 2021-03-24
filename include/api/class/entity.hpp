
/**
 * @file entity.hpp
 * @author @Aalexdev (aaleex394@gmail.com)
 * @brief the Entity file
 * @version 0.0.1
 * 
 * @copyright (c) 2021 Aalex
 * 
 * MIT License
 *
 *  Copyright (c) 2021 Aalex
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions: 
 * 
 * The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */


/**
 * @file entity.hpp
 * 
 * Header file for Entity, Entity_type, Part, Part_type, Part_Type_list class and methode managment
 * 
 */
#ifndef __ENTITY__
#define __ENTITY__

    #include <iostream>
    #include <vector>
    #include <cstring>
    #include <SDL2/SDL.h>

    using namespace std;

    class Entity;

    #include "api/io/xml.hpp"
    #include "api/functions/texture.hpp"
    #include "api/functions/math.hpp"
    #include "api/class/equipment.hpp"
    #include "ui/graphics/light.hpp"
    #include "ui/graphics/particles.hpp"


    struct Entity_point{
        int x, y;
        int distFromCenter;
        int additionnalAngle;
    };

    struct Entity_Equipment{

        int x, y;
        int distFromCenter;
        int additionnalAngle;

        int minAngle;
        int maxAngle;

        int id;
    };

    enum TurnType{
        Turnfree,
        Turnmul,
        Turndiv,
        Turnsub,
        Turnadd
    };

    class Entity_type{
        public:
            Entity_type();
            ~Entity_type();

            /**
             * @brief load the type from a XMLNode
             * 
             * @param node the XMLNode
             * @return * retun true when it's loaded, false on error
             */
            bool load_from_xml(XMLNode* node);

            /**
             * @brief Get the name object
             * 
             * @return * return the name of the type
             */
            string get_name(void){return this->name;}

            /**
             * @brief Get the Texture object
             * 
             * @return * return the texture of the type
             */
            SDL_Texture* getTexture(void){return this->texture;}

            /**
             * @brief Get the Rect object
             * 
             * @return * return the rect of the type
             */
            SDL_Rect getRect(void){return this->rect;}

            /**
             * @brief Get the Mass object
             * 
             * @return * return the mass of the type
             */
            float getMass(void){return this->mass;}

            /**
             * @brief Get the Strength object
             * 
             * @return * return the engine strength of the type
             */
            float getStrength(void){return this->strength;}

            /**
             * @brief Get the Layer Min object
             * 
             * @return * return the minimal layer of the type (z axis)
             */
            int getLayerMin(void){return this->layerMin;}

            /**
             * @brief Get the Layer Max object
             * 
             * @return * return the maximal layer of the type (z axis)
             */
            int getLayerMax(void){return this->layerMax;}

            /**
             * @brief Get the Max Speed object
             * 
             * @return * return the maximal speed of the type
             */
            int getMaxSpeed(void){return this->maxSpeed;}

            /**
             * @brief Get the Min Speed object
             * 
             * @return * return the minimal speed of the type
             */
            int getMinSpeed(void){return this->minSpeed;}

            /**
             * @brief Get the Turn Type
             * 
             * @return * return the type of turn 
             */
            TurnType getTurnType(void){return turnType;}

            /**
             * @brief Get the Turn Value
             * 
             * @return * return the trun's vlaue 
             */
            int getTurnValue(void){return turnValue;}

            /**
             * @brief get the maximale angle speed
             * 
             */
            float getMaxRotarySpeed(void){return maxRotarySpeed;}

            /**
             * @brief get the parts vector of the type
             * 
             * @return * return the hitbox of the type
             */
            Entity_point* getPart(void);

            /**
             * @brief get the max health of the type
             * 
             * @return return the max health 
             */
            int getHealth(void);

            /**
             * @brief get the length of the part tab
             * 
             * @return return the length 
             */
            int getPartSize(void);

            /**
             * @brief get the eqipments points
             * 
             * @return Entity_point* 
             */
            Entity_Equipment* getEquipment(void);

            /**
             * @brief Get the Equipment Size object
             * 
             * @return int 
             */
            int getEquipmentSize(void);

            /**
             * @brief actions when the health is nul or negative
             * 
             */
            struct OnDeath{
                /**
                 * @brief the targeting layer
                 * 
                 */
                int z;

                /**
                 * @brief time before the entity is delete, in ms
                 * 
                 */
                int time;
            };

            OnDeath* getDeath(void);

        private:
            /**
             * @brief the name of the type
             * 
             */
            string name;

            /**
             * @brief the texture of the type
             * 
             */
            SDL_Texture* texture;

            /**
             * @brief the size of the type
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the minimal and the maximal layer (z axis) of the type
             * 
             */
            int layerMax, layerMin;

            /**
             * @brief the maximal and the minimal speed of the type
             * 
             */
            int maxSpeed, minSpeed;

            /**
             * @brief Get if the name is early used by another type
             * 
             * @param name the name of the entity
             * @return * return true if the name is early used, false otherwise
             */
            bool used_name(string name);
            /**
             * @brief the mass of the type
             * 
             */
            float mass;

            /**
             * @brief the engine strenght
             * 
             */
            float strength;

            /**
             * @brief the type of the turn
             * 
             */
            TurnType turnType;

            /**
             * @brief the value linked with the type of the turn
             * 
             */
            int turnValue;

            /**
             * @brief the maximal rotary speed
             * 
             */
            float maxRotarySpeed;

            /**
             * @brief the entity's hibox
             * 
             */
            Entity_point* part;

            /**
             * @brief the maximal health of the type
             * 
             */
            int health;

            /**
             * @brief 
             * 
             */
            int partSize;

            /**
             * @brief equipment points
             * 
             */
            Entity_Equipment* equipments;

            /**
             * @brief the equipment tab size
             * 
             */
            int equipments_len;

            /**
             * @brief actions to do
             * 
             */
            OnDeath* onDeath;
    };

    class Entity{
        public:
            Entity();
            Entity(bool isPlayer);
            ~Entity();

            /**
             * @brief set the type of the entity
             * 
             * @param name the name of the type
             * @return * return true if the name has been founded, false on error
             */
            bool set(string name);

            /**
             * @brief update the entity
             * 
             * @return * return nothing 
             */
            void update(void);

            /**
             * @brief draw the entity on the renderer
             * 
             * @return return true if everything is working, false otherwise
             */
            bool draw(void);

            /**
             * @brief Get the Z axis
             * 
             * @return * return the z axis
             */
            int getZ(void){return this->z;}

            /**
             * @brief Get the X axis
             * 
             * @return * return the x axis
             */
            int getX(void){return this->rect.x;}

            /**
             * @brief Get the Y axis
             * 
             * @return * return the y axis
             */
            int getY(void){return this->rect.y;}

            /**
             * @brief Get the width of the entity
             * 
             * @return * return the width of the entity
             */
            int getW(void){return this->rect.w;}

            /**
             * @brief Get the height of the entity
             * 
             * @return * return the height of the entity
             */
            int getH(void){return this->rect.h;}

            /**
             * @brief load the entity from a XMLNode
             * 
             * @param node the XMLNode
             * @return * return true if loaded, false otherwise
             */
            bool load_from_xml(XMLNode* node);

            /**
             * @brief Get if the entity is linked with a type
             * 
             * @return * return if the entity is linked with a type
             */
            bool is_linked(void){return this->type;}

            /**
             * @brief unlinkthe entity of the linked type
             * 
             * @return * return nothing
             */
            void unlink(void);

            /**
             * @brief Get the angle of the entity (int)
             * 
             * @return * return the angle of the entity
             */
            int getAngle(void){return this->angle;}

            /**
             * @brief Get the angle of the entity (float)
             * 
             * @return * return the float value of the entity
             */
            float getAngleF(void){return this->angle;}

            /**
             * @brief Get the pointer the the angle of the entity
             * 
             * @return * return the pointer of the angle
             */
            float* getAngle_ptr(void){return &this->angle;}
            
            /**
             * @brief Get the is_player object
             * 
             * @return * return is the entity is player 
             */
            bool isPlayer(void){return this->is_player;}

            /**
             * @brief set points of the part into the Point
             * 
             * @param p the point tab
             */
            void getPart(Point **p);

            /**
             * @brief set points of the equipment into the Point
             * 
             * @param the point tab
             */
            void getEquipment(Point **p);

            /**
             * @brief calculate light
             * 
             */
            void calculateLights(void);

            /**
             * @brief draw light from the 
             * 
             * @param i the actual layer height of the drawing
             * 
             * @return retrun true if drawn or ignore, false on error
             */
            bool drawLight(int i);

            /**
             * @brief get the type of the entity
             * 
             * @return return the type
             */
            Entity_type* getType(void);

            /**
             * @brief retrun true if the entity is in the screen
             * 
             */
            bool in_screen(void);

            /**
             * @brief retur true if the input point is inside the entity' hitbox
             * 
             * @param x the x axis
             * @param y the y axis
             * @return return true if inside, false otherwise 
             */
            bool PointInside(int x, int y);

            /**
             * @brief Set the Health object
             * 
             * @param health 
             */
            void setHealth(int health);

            /**
             * @brief kill the entity
             * 
             */
            void kill(void);

            /**
             * @brief retunr true if the entity should be deleted
             * 
             */
            bool should_delete(void);

        private:

            /**
             * @brief the pointer to the type of the entity
             * 
             */
            Entity_type* type;

            /**
             * @brief the angle of the entity (from 0 to 359)
             * 
             */
            float angle;

            /**
             * @brief the z axis
             * 
             */
            float z;

            /**
             * @brief the rect of the entity; (position and size)
             * 
             */
            SDL_Rect rect;

            /**
             * @brief if the entity is the player
             * 
             */
            bool is_player;

            /**
             * @brief the acceleration of the entity
             * 
             */
            float acceleration;

            /**
             * @brief the speed of the entity (px per refresh)
             * 
             */
            float speed;

            /**
             * @brief the strength generated by the engine
             * 
             */
            float strength;

            /**
             * @brief the rotary acceleration
             * 
             */
            float turn_acceleration;

            /**
             * @brief the speed of rotation (angle per repfresh)
             * 
             */
            float turn_speed;

            /**
             * @brief the rotary strenght
             * 
             */
            float turn_strength;

            /**
             * @brief if the entity is mouving and if ti's turning
             * 
             */
            bool is_mouving, is_turn;

            /**
             * @brief the tick beetween two refresh for the mouving and the rotary engine
             * 
             */
            int mouving_ticks, turn_ticks;

            /**
             * @brief reset vars of the entity
             * 
             * @return * return nothing
             * 
             */
            void reset(void);

            /**
             * @brief the center of the boat on the map
             * 
             */
            Point center;

            /**
             * @brief parts of the entity;
             * 
             */
            Entity_point* part;

            /**
             * @brief the health of the entity
             * 
             */
            int health;

            /**
             * @brief 
             * 
             */
            Entity_point* equipmentsP;

            /**
             * @brief the equipment tab 
             * 
             */
            Equipment** equipments;

            /**
             * @brief draw the hitbox of the entity
             * 
             * @return return true if drawn, false on error
             */
            bool drawHitbox(void);

            /**
             * @brief draw points where equipments can be
             * 
             * @return return true if drawn, false on error
             */
            bool drawEquipmentPoint(void);

            /**
             * @brief update equipments position
             * 
             */
            void updateEquipmentPos(void);

            /**
             * @brief update equipments (position and ammunitions)
             * 
             */
            void updateEquipments(void);

            /**
             * @brief set whene the entity's health if less or equal to zero
             * 
             */
            struct OnDeath{
                /**
                 * @brief ticks used for the animation
                 * 
                 */
                int tick;
            };

            /**
             * @brief the death struct, NULL if alive
             * 
             */
            OnDeath* onDeath;

            /**
             * @brief 
             * 
             */
            bool should_del;

            /**
             * @brief the entity's object struct
             * 
             */
            struct objectAttribute{
                int dist;
                int angle;
            };

            /**
             * @brief particles of the entity
             * 
             */
            vector<Particles*> particles;

            /**
             * @brief points of the particle
             * 
             */
            vector<objectAttribute*> particles_point;

            /**
             * @brief lights of the entity
             * 
             */
            vector<Light*> lights;

            /**
             * @brief points of the particle
             * 
             */
            vector<objectAttribute*> lights_points;

            /**
             * @brief update particles's position from the pos and the angle of the entity
             * 
             */
            void setParticlesPos(void);

            /**
             * @brief update lights's position from the position and the angle of the entity
             * 
             */
            void setLightsPos(void);

            /**
             * @brief get the centered x from the map
             * 
             * @return int 
             */
            int getCenteredX(void);

            /**
             * @brief get the centered y from the map
             * 
             * @return int 
             */
            int getCenteredY(void);
    };

#endif