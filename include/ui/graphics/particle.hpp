#ifndef __PARTICLE__
#define __PARTICLE__

    #include <SDL2/SDL.h>

    /**
     * @brief the particle is a colored point who has no collisions
     * 
     */
    class Particle{
        public:
            /**
             * @brief Construct a new Particle object
             * 
             */
            Particle();

            /**
             * @brief Destroy the Particle object
             * 
             */
            ~Particle();

            /**
             * @brief get the position of the particle in a int point structure
             * 
             * @return SDL_Point, int x and int y
             */
            SDL_Point pos(void);

            /**
             * @brief get the position of the particle in a float point structure
             * 
             * @return SDL_FPoint, float x and float y
             */
            SDL_FPoint posf(void);

            /**
             * @brief set the position of the particle
             * 
             * @param p a int point
             */
            void pos(SDL_Point p);

            /**
             * @brief set the position of the particle
             * 
             * @param p a float points
             */
            void posf(SDL_FPoint p);

            /**
             * @brief get the vector of the particle in a int pointe structure
             * 
             * @return SDL_Point 
             */
            SDL_Point vector(void);

            /**
             * @brief get the vector of the particle in a float pointe structure
             * 
             * @return SDL_FPoint 
             */
            SDL_FPoint vectorf(void);

            /**
             * @brief set the vector of the particle
             * 
             * @param p a int point
             */
            void vector(SDL_Point p);

            /**
             * @brief set the vector of the particle
             * 
             * @param p a float point
             */
            void vectorf(SDL_FPoint p);

            /**
             * @brief get the color of the particle
             * 
             * @return SDL_Color 
             */
            SDL_Color color(void);

            /**
             * @brief get the pointer to the color
             * 
             * @return SDL_Color* 
             */
            SDL_Color* color_ptr(void);

            /**
             * @brief set the color of the particle
             * 
             * @param color the color
             */
            void color(SDL_Color color);

            /**
             * @brief set the position of the vector with a random number
             * 
             * @param radius the max distance of the vector
             */
            void create_random_vector(int radius);

            /**
             * @brief set the position of the vector with a random number
             * 
             * @param radius the max distance of the vector
             */
            void create_random_vectorf(int radius);

            /**
             * @brief set the max range of the particle
             * 
             * @param range the max range
             */
            void range(int range);

            /**
             * @brief set the angle of the particle
             * 
             * @param angle the angle
             */
            void angle(int angle);

            /**
             * @brief update the position of the particle
             * 
             */
            void update(void);

            /**
             * @brief draw a point on the renderer at the position
             * 
             * @return true if drawn, false on error
             */
            bool draw(void);

            /**
             * @brief get if the particle had to be delete
             * 
             * @return true if it is, false if not
             */
            bool del(void);

            /**
             * @brief get the duration of the particle in miliseconds
             * 
             * @return int 
             */
            int duration(void);

            /**
             * @brief set the duration of the particle, in miliseconds
             * 
             * @param duration the duration
             */
            void duration(int duration);

            /**
             * @brief get ticks at the particle init
             * 
             * @return int 
             */
            int ticks(void);

            /**
             * @brief set the ticks of the particle
             * 
             * @param ticks 
             */
            void ticks(int ticks);

        private:

            /**
             * @brief the position of the particle
             * 
             */
            SDL_FPoint _pos;

            /**
             * @brief the vector of the particle, will be added to the pos
             * 
             */
            SDL_FPoint _vector;

            /**
             * @brief the color of the particle
             * 
             */
            SDL_Color _color;

            /**
             * @brief the angle of the Particles object
             * 
             */
            int _angle;

            /**
             * @brief the max range of the particle
             * 
             */
            int _range;

            /**
             * @brief
             * 
             */
            bool _del;

            /**
             * @brief return a random angle 
             * 
             * @return int 
             */
            int random_angle(void);

            /**
             * @brief the duration of the particle
             * 
             */
            int _duration;

            /**
             * @brief ticks at the particle init
             * 
             */
            int _ticks;
    };

    Particle* create_Particle(void);
    void delete_Particle(Particle* p);

#endif