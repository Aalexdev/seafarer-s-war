#ifndef __PARTICLES_TYPE__
#define __PARTICLES_TYPE__

    #include "api/io/xml.hpp"

    #include <SDL2/SDL.h>
    #include <iostream>
    #include <vector>
    using namespace std;

    class Particles_type{
        public:
            /**
             * @brief Construct a new Particles_type object
             * 
             */
            Particles_type();

            /**
             * @brief Destroy the Particles_type object
             * 
             */
            ~Particles_type();

            /**
             * @brief load the particles type form a xml Node
             * 
             * @param node the xml node
             * @return true if loaded, false on error
             */
            bool load(XMLNode* node);

            /**
             * @brief get the name of the type
             * 
             * @return string 
             */
            string name(void);

            /**
             * @brief set the type's name
             * 
             * @param name the new name of the type
             */
            void name(string name);

            /**
             * @brief get color of the particle
             * 
             * @return vector<SDL_Color*> 
             */
            vector<SDL_Color*> colors(void);

            /**
             * @brief get a random color from the colors vector
             * 
             * @return SDL_Color 
             */
            SDL_Color get_random_color(void);

        private:
            /**
             * @brief the name of the particle
             * 
             */
            string _name;

            /**
             * @brief color of the type
             * 
             */
            vector<SDL_Color*> _colors;
            
            /**
             * @brief push a new color into the colors vector from a xml node
             * 
             * @param color_node the xml color node
             */
            void pushColor(XMLNode* color_node);
    };
    
    /**
     * @brief get a particles_type from a name
     * 
     * @param name the name of the particle
     * @return Particles_type* 
     */
    Particles_type* search_particle_type(string name);

    /**
     * @brief push a particle type into the particles_type vector and load it from a xml node
     * 
     * @param node the xml node
     */
    void push_particle_type(XMLNode* node);
    
    /**
     * @brief clear the particles_type vector
     * 
     */
    void clear_particles_type(void);

    // operators
    bool operator==(Particles_type* t, string name);

#endif