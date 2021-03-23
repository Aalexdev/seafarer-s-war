#ifndef __EQUIPMENT__
#define __EQUIPMENT__

    #include <iostream>
    #include <cstring>
    #include <SDL2/SDL.h>

    using namespace std;

    class Equipment;
    class Equipment_type;

    #include "api/functions/texture.hpp"
    #include "api/class/entity.hpp"
    #include "api/class/ammunition.hpp"
    #include "ui/graphics/particles.hpp"
    #include "ui/graphics/light.hpp"

    #define UNKNOWN_AMMUNITION "unknown"
    
    class Equipment_type{
        public:
            /**
             * @brief Construct a new Equipment_type object
             * 
             */
            Equipment_type();

            /**
             * @brief Destroy the Equipment_type object
             * 
             */
            ~Equipment_type();

            /**
             * @brief load the equipement from a XMLNode
             * 
             * @param node the xml node
             * @return return true if loaded, false on error
             */
            virtual bool loadXML(XMLNode* node);  

            /**
             * @brief Get the Light type name
             * 
             * @return return the light type name, use bool Light::set(type); 
             */
            string getLight(void);

            /**
             * @brief the cannon struct
             * 
             */
            struct Cannon{
                /**
                 * @brief the couldown beetween every shot
                 * 
                 */
                int couldown;

                /**
                 * @brief the type of ammunition used, unknown to use every types
                 * 
                 */
                string ammunition_type;

                /**
                 * @brief type used for particles
                 * 
                 */
                string particle_type;
            };

            /**
             * @brief Get the Cannon object
             * 
             * @return retunr the cannon pointer
             */
            Cannon* getCannon(void);

            /**
             * @brief get the center of the equipment
             * 
             * @return return the center
             */
            SDL_Point* getCenter(void);

            /**
             * @brief Get the Texture of the equipment
             * 
             * @return return the texture
             */
            SDL_Texture* getTexture(void);

            /**
             * @brief Get the rect to get the size of the cannon
             * 
             * @return return the rect 
             */
            SDL_Rect getRect(void);

            /**
             * @brief Get the name of the type
             * 
             * @return return the name
             */
            string getName(void);

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
            SDL_Texture *texture;

            /**
             * @brief the texture size
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the rotaionnal center
             * 
             */
            SDL_Point center;

            /**
             * @brief the angle
             * 
             */
            int angle;

            /**
             * @brief delay beetween every deg, in mili second
             * 
             */
            int delay;

            /**
             * @brief destroy the texture and let free the allocated memory
             * 
             */
            void freeTexture(void);

            /**
             * @brief the light type name
             * 
             */
            string light;

            /**
             * @brief 
             * 
             */
            Cannon* cannon;

    };

    /**
     * @brief 
     * 
     */
    class Equipment{
        public:
            /**
             * @brief Construct a new Equipment object
             * 
             */
            Equipment(Entity* parent);

            /**
             * @brief Destroy the Equipment object
             * 
             */
            ~Equipment();

            /**
             * @brief draw the equipment light
             * 
             */
            bool drawLight(void);

            /**
             * @brief draw the equipment
             * 
             */
            bool draw(void);

            /**
             * @brief update the equipment
             * 
             */
            void update(void);

            /**
             * @brief the cannon struct, store all cannons data
             * 
             */
            struct Cannon{
                /**
                 * @brief ammunitions of the cannon
                 * 
                 */
                vector<Ammunition*> ammunitions;

                /**
                 * @brief ticks used by the couldown 
                 * 
                 */
                int tick;

                /**
                 * @brief the shoot particle animation
                 * 
                 */
                Particles* particles;
            };

            /**
             * @brief set the type of the quipment from a name
             * 
             * @param name the type's name
             * @return return true if type found, false on error
             */
            bool setType(string name);

            /**
             * @brief an id, used by entity to set the position and the maximal range
             * 
             */
            int id;

            /**
             * @brief the target structure where a stored targeting types
             * 
             */
            struct Targets{
                /**
                 * @brief set the equipment on a targeting angle, the equipment will automaticly turn at the rotary speed
                 * 
                 */
                struct SpeedTarget{
                    int rotarySpeed;
                };

                /**
                 * @brief set the equipment on a targeting position, the equipment will automaticly lock at the position
                 * 
                 */
                struct PosTarget{
                    /**
                     * @brief x axis
                     * 
                     */
                    int x;

                    /**
                     * @brief y axis
                     * 
                     */
                    int y;
                };

                /**
                 * @brief the target union, used by the equipment
                 * 
                 */
                union Target{
                    SpeedTarget speed;
                    PosTarget pos;
                };

                enum TargetType{
                    target_speed,
                    target_pos
                };
            };

            /**
             * @brief Set the targeting angle
             * 
             * @param angle targeting angle
             */
            void setTarget(int angle);

            /**
             * @brief Set the Angle of the equipment
             * 
             * @param angle the new angle
             */
            void setAngle(int angle);

            /**
             * @brief Set the targeting angle
             * 
             * @param angle the angle target
             */
            void setAngleTarget(int angle);

            /**
             * @brief Set the Target position (from teh screen)
             * 
             * @param x 
             * @param y 
             */
            void setTarget(int x, int y);

            /**
             * @brief Set the position (from the center) of the equipment
             * 
             * @param x the x axis
             * @param y the y axis
             */
            void setPos(int x, int y);

            /**
             * @brief Set the limit of the angle
             * 
             * @param min the minimal angle
             * @param max the maximal angle
             */
            void setAngleLimit(int min, int max);

            /**
             * @brief launch an ammunition, only of the equipment is a cannon
             * 
             */
            void shot(void);
            
        
        private:
            /**
             * @brief the parent if the equipment
             * 
             */
            Entity* parent;

            /**
             * @brief the linked type
             * 
             */
            Equipment_type* type;

            /**
             * @brief 
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the light
             * 
             */
            Light* light;

            /**
             * @brief the cannon struct
             * 
             */
            Cannon* cannon;

            /**
             * @brief the angle of the equipment
             * 
             */
            int angle;

            /**
             * @brief the targeting angle
             * 
             */
            int angleTarget;

            /**
             * @brief unlink the equipment to his type and destroy the allocated memory
             * 
             */
            void unlink(void);

            /**
             * @brief the maximal angle
             * 
             */
            int angleMax;

            /**
             * @brief the minimal angle
             * 
             */
            int angleMin;

            /**
             * @brief the target of the equipment
             * 
             */
            Targets::Target target;

            /**
             * @brief the type of the actal targeting type
             * 
             */
            Targets::TargetType targetType;

            /**
             * @brief get the centered x of the equipment
             * 
             * @return return the centered x
             */
            int getX(void);

            /**
             * @brief get the centered y of the equipment
             * 
             * @return return the centered y
             */
            int getY(void);

            
    };

#endif