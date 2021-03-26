#ifndef __ANIMATION__
#define __ANIMATION__

    #include <iostream>
    #include <vector>
    #include <string>

    #include "ui/graphics/particles_type.hpp"

    using namespace std;
    
    class Particles{
        public:
            /**
             * @brief Construct a new Particles object
             * 
             */
            Particles();

            /**
             * @brief Destroy the Particles object
             * 
             */
            ~Particles();

            /**
             * @brief the particule struct
             * 
             */
            struct Particle{
                /**
                 * @brief the vector of the particle
                 * 
                 */
                SDL_FPoint vector;

                /**
                 * @brief the position of the screen of the particle
                 * 
                 */
                SDL_FPoint pos;

                /**
                 * @brief the tick
                 * 
                 */
                int tick;
                
                enum Sub_Particle{
                    Particle_subX,
                    Particle_subY
                };

                /**
                 * @brief on update, it will sub the x value of the vector or the y value
                 * 
                 */
                Sub_Particle sub;

                /**
                 * @brief the color of the particle
                 * 
                 */
                int r, g, b, a;

                /**
                 * @brief the light effect of the particles
                 * 
                 */
                Light* light;
            };  

            /**
             * @brief push a praticle into the particle vector
             * 
             */
            void pushParticle(void);

            /**
             * @brief get the Z axis of the animation
             * 
             * @return retur the Z axis
             */
            int getZ(void);

            /**
             * @brief set the Z axis of the animation
             * 
             * @param z the new Z axis
             */
            void setZ(int z);

            /**
             * @brief draw lights effects of the animation
             * 
             * @param z the actual height of the layer
             * @return return true if drawn, false on error
             */
            bool drawLight(int z);

            /**
             * @brief draw particles of the animation
             * 
             * @param z the actual height of the layer
             * @return return true if draw, false on error
             */
            bool draw(int z);

            /**
             * @brief update particles 
             * 
             */
            void update(void);

            /**
             * @brief set the type of the particles from a string
             * 
             * @param type_name the name of the type
             * @return return true if type found, false on error 
             */
            bool set(string type_name);

            /**
             * @brief set the position of the particle
             * 
             * @param x the x axis 
             * @param y the y axis
             */
            void setPos(int x, int y);

            /**
             * @brief set the range of the particle
             * 
             * @param range the ew range, in degres
             */
            void setRange(int range);

            /**
             * @brief set the angle of the particle
             * 
             * @param angle teh new angle
             */
            void setAngle(int angle);

            /**
             * @brief set the duration of the particle
             * 
             * @param duration the duration
             */
            void setDuration(int duration);

            /**
             * @brief get if the paricle should be delete
             * 
             * @return return true if should be delete, false if not
             */
            bool should_delete(void);

            /**
             * @brief set the push member, push particles only if it's true
             * 
             * @param push 
             */
            void push(bool push);

            /**
             * @brief Get the Type object
             * 
             * @return Particles_type* 
             */
            Particles_type* getType(void);

        private:
            /**
             * @brief the linked type of the particles
             * 
             */
            Particles_type* type;

            /**
             * @brief particles of the animation
             * 
             */
            vector<Particle*> particles;

            /**
             * @brief the z axis of the animation
             * 
             */
            int z;

            /**
             * @brief the angle of the particles
             * 
             */
            int angle;

            /**
             * @brief the range
             * 
             */
            int range;

            /**
             * @brief the position of the particle
             * 
             */
            SDL_Point pos;

            /**
             * @brief unlink the particle from a type
             * 
             */
            void unlink(void);

            /**
             * @brief get a random angle between angle - (range/2) and angle + (range/2)
             * 
             * @return return an angle
             */
            int getRandAngle(void);

            /**
             * @brief get a rabdom color canal
             * 
             * @return return an int between 0 and 255 
             */
            int getR(void);
            int getG(void);
            int getB(void);
            int getA(void);

            /**
             * @brief colors used to get a degraded
             * 
             */
            SDL_Color colorIndex;

            /**
             * @brief the tick of the particle, will be destroyed whene SDL_GetTicks() is greater or equal to tick
             * 
             */
            int tick;

            /**
             * @brief push particles inn the vector
             * 
             */
            void pushParticles(void);

            /**
             * @brief push particles only if it's true
             * 
             */
            bool pushing;
    };

    Particles* operator<<(Particles* p, string name);
    bool operator==(Particles* p, string name);

    int update_particles(void* ptr);
    void draw_particles(int z);
    void clear_particles(void);


#endif