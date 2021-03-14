#ifndef __ANIMATION__
#define __ANIMATION__

    #include "ui/graphics/sprite.hpp"

    class Animation{
        public:
            Animation();
            ~Animation();

            /**
             * @brief Set the duration of the effect
             * 
             * @param duration 
             */
            void setDuration(int duration);

            /**
             * @brief return the pointer of the duration
             * 
             * @return int* 
             */
            int* Duration(void);

            /**
             * @brief get the duration of the animation
             * 
             * @return int 
             */
            int getDuration(void);

            /**
             * @brief set the x axis
             * 
             * @param x the centered x axis if the animation 
             */
            void setX(int x);

            /**
             * @brief set the y axis
             * 
             * @param y the centered y axis if the animation
             */
            void setY(int y);

            /**
             * @brief return if the animation should be destroyed
             * 
             * @return return true if the animation if the animation hed te be destroyed, false otherwise
             */
            bool destroy(void);

            /**
             * @brief set the sprite from a name
             * 
             * @param sprite_name the name of the sprite type
             * @return return true if name is found, false on error
             */
            bool setSprite(string sprite_name);

        private:
            /**
             * @brief the duartion of the animation, in miliseconds
             * 
             */
            int duration;

            /**
             * @brief the sprites vector
             * 
             */
            vector<Sprite*> sprites;
    };

#endif