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
             * @brief the light struct
             * 
             */
            struct Light{
                /**
                 * @brief the power of the light
                 * 
                 */
                int power;

                /**
                 * @brief the maximal range
                 * 
                 */
                int maxRange;
            };

            /**
             * @brief Get the Light object
             * 
             * @return return the light pointer 
             */
            Light* getLight(void);

            /**
             * @brief the cannon struct
             * 
             */
            struct Cannon{
                // soon
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
             * @brief the light struct
             * 
             */
            Light* light;

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
            Equipment();

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
             * @brief the equipment struct, used  by equipment
             * 
             */
            struct Light{
                /**
                 * @brief the actual range
                 * 
                 */
                int range = 30;

                // soon
            };

            struct Cannon{
                // soon
            };

            bool setType(string name);

            /**
             * @brief an id, used by entity to set the position and the maximal range
             * 
             */
            int id;

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
        
        private:
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
             * @brief the light struct
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

            int angleTarget;


            void unlink(void);

    };

#endif