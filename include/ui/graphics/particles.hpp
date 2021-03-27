#ifndef __ANIMATION__
#define __ANIMATION__

    #include <iostream>
    #include <vector>
    #include <string>

    #include "ui/graphics/particles_type.hpp"
    #include "ui/graphics/particle.hpp"

    using namespace std;

    #define PARTICLES_DURATION_UNLIMITED 92738273
    #define PARTICLES_DUARTION_EMPTY 92783762 
    
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
             * @brief get the type of the particle
             * 
             * @return Particles_type* 
             */
            Particles_type* type(void);

            /**
             * @brief set the type of the particles
             * 
             * @param type the new type
             */
            void type(Particles_type* type);

            /**
             * @brief set the particles's type from a name
             * 
             * @param type_name the type's name
             * @return true if found, false if not
             */
            bool type(string type_name);

            /**
             * @brief get the particles vector
             * 
             * @return vector<Particle*> 
             */
            vector<Particle*> particles(void);

            /**
             * @brief push a new Particle in the particles vector
             * 
             */
            void push(void);        

            /**
             * @brief get the radius of particles
             * 
             * @return float 
             */
            float radius(void);

            /**
             * @brief set the particles's radius
             * 
             * @param radius the new radius
             */
            void radius(float radius);

            /**
             * @brief get the particles angle
             * 
             * @return int 
             */
            int angle(void);

            /**
             * @brief set the particles angle
             * 
             * @param angle the new angle
             */
            void angle(int angle);

            /**
             * @brief get the particles range
             * 
             * @return int 
             */
            int range(void);

            /**
             * @brief set the particles range
             * 
             * @param range the new range
             */
            void range(int range);

            /**
             * @brief get the positon of the particles
             * 
             * @return SDL_Point 
             */
            SDL_Point pos(void);

            /**
             * @brief set the position of the particle
             * 
             * @param pos the new position
             */
            void pos(SDL_Point pos);

            /**
             * @brief get the density of the particle
             * 
             * @return float 
             */
            float density(void);

            /**
             * @brief set the density if the particle
             * 
             * @param density the new density
             */
            void density(float density);

            /**
             * @brief update the particle
             * 
             */
            void update(void);

            /**
             * @brief draw particles on the renderer
             * 
             * @return trueif drawn, false on error
             */
            bool draw(int z);

            /**
             * @brief get the Z axis
             * 
             * @return int 
             */
            int z(void);

            /**
             * @brief set the z axis
             * 
             * @param z the new z
             */
            void z(int z);

            /**
             * @brief set the pushing member, if it's false, it's wont push particles
             * 
             * @param pushing the push var
             */
            void pushing(bool pushing);

            /**
             * @brief get if the particles had to be delete
             * 
             * @return true if it is, false if not
             */
            bool del(void);

            /**
             * @brief get the duration of the particle
             * 
             * @return int 
             */
            int duration(void);

            /**
             * @brief set the duration of the particle
             * 
             * @param duration the new duration
             */
            void duration(int duration);

            /**
             * @brief get the duration of particles
             * 
             * @return int 
             */
            int particles_duration(void);

            /**
             * @brief set the duration of particles
             * 
             * @param duration the new duration
             */
            void particles_duration(int duration);

        private:
            /**
             * @brief the type of the particle
             * 
             */
            Particles_type* _type;

            /**
             * @brief the vector of particles
             * 
             */
            vector<Particle*> _particles;

            /**
             * @brief the particles's vector max
             * 
             */
            float _radius;

            /**
             * @brief the angle of particles
             * 
             */
            int _angle;

            /**
             * @brief the range of particles
             * 
             */
            int _range;

            /**
             * @brief the position of the particle
             * 
             */
            SDL_Point _pos;

            /**
             * @brief the density of the particles, particles pushed per miliseconds
             * 
             */
            float _density;

            /**
             * @brief the z axis of the particle
             * 
             */
            int _z;

            /**
             * @brief push particles only if it's true
             *
             */
            bool _pushing;

            /**
             * @brief the duarition of the particle, in miliseconds
             * 
             */
            int _duration;

            /**
             * @brief ticks att the init of the particle
             * 
             */
            int _ticks;

            /**
             * @brief 
             * 
             */
            bool _del;

            /**
             * @brief the duration of particles
             * 
             */
            int _particles_duration;
    };

    Particles* operator<<(Particles* p, string name);
    bool operator==(Particles* p, string name);

    Particles* create_particle(void);
    int update_particles(void* ptr);
    void draw_particles(int z);
    void clear_particles(void);


#endif