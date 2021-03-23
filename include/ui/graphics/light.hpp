#ifndef __LIGHT__
#define __LIGHT__

    #include "api/io/xml.hpp"
    #include <SDL2/SDL.h>

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

    class Light_type{
        public:
            /**
             * @brief Construct a new Light_type object
             * 
             */
            Light_type();

            /**
             * @brief Destroy the Light_type object
             * 
             */
            ~Light_type();

            /**
             * @brief load the light effect type from a xml node
             * 
             * 
             * @param node the xml node
             * @return return true if loaded, false on error
             */
            bool load(XMLNode* node);

            /**
             * @brief get the name of the light 
             * 
             * @return return the name
             */
            string getName(void);

            /**
             * @brief get the size of the light
             * 
             * @return return the size 
             */
            SDL_Rect getSize(void);

            /**
             * @brief get the texture of the light type
             * 
             * @return return a texture
             */
            SDL_Texture* getTexture(void);

            /**
             * @brief get the pointer to the rotationnal center of the light
             * 
             * @return retunr the rotrationna center
             */
            SDL_Point* getCenter(void); 

        private:
            /**
             * @brief the name of the light
             * 
             */
            string name;

            /**
             * @brief the texture of the light
             * 
             */
            SDL_Texture* texture;

            /**
             * @brief the size of the texture
             * 
             */
            SDL_Rect size;

            /**
             * @brief the rotationnal center of the light
             * 
             */
            SDL_Point center;
    };

    class Light{
        public:
            /**
             * @brief Construct a new Light object
             * 
             */
            Light();

            /**
             * @brief Destroy the Light object
             * 
             */
            ~Light();

            /**
             * @brief set the type of the light
             * 
             * @param name the name of the light type
             * @return return true if loaded, false on error
             */
            bool set(string name);

            /**
             * @brief draw the light on the renderer
             * 
             * @param z the layer's hight, will not draw if it's not the light's z member
             * @return retunr true if drawn, false on error
             */
            bool draw(int z);

            /**
             * @brief set the position of the light
             * 
             * @param x the X axis
             * @param y the Y axis
             */
            void setPos(int x, int y);

            /**
             * @brief set the size of the light
             * 
             * @param w the width of the texture
             * @param h the height of the texture
             */
            void setSize(int w, int h);

            /**
             * @brief reset the size of the texture and take the original size
             * 
             */
            void resetSize(void);

            /**
             * @brief set the angle of the light
             * 
             * @param angle 
             */
            void setAngle(int angle);

            /**
             * @brief set the hight if the light
             * 
             * @param z the new hight
             */
            void setZ(int z);
        
        private:
            /**
             * @brief the type linked with the light
             * 
             */
            Light_type* type;

            /**
             * @brief the position and the size of the light
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the angle of the light
             * 
             */
            int angle;

            /**
             * @brief the hight of the light
             * 
             */
            int z;
    };

    Light_type* searchLight(string name);
    void pushLight_type(XMLNode* node);
    void clearLights(void);
    Light* newLight(void);

#endif