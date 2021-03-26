#ifndef __PARTICLES_TYPE__
#define __PARTICLES_TYPE__

    #include "api/io/xml.hpp"
    #include "api/functions/math.hpp"
    #include "ui/graphics/light.hpp"

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
             * @brief loadthe effect type from a XML node
             * 
             * @param node the xml node
             * @return return true if loaded, false on error
             */
            bool load(XMLNode* node);

            struct Particle_Circle{
                /**
                 * @brief the radius of the circle
                 * 
                 */
                int radius;

                /**
                 * @brief if true, it will draw filled circle, empty if not
                 * 
                 */
                bool filled;
            };

            struct Particle_Square{
                /**
                 * @brief the width of the square
                 * 
                 */
                int width;

                /**
                 * @brief if true, it will draw filled square, empty if not
                 * 
                 */
                bool filled;
            };

            struct Particle_Point{

            };

            struct Particle_Ellipse{
                /**
                 * @brief the horisontal radius of the particle
                 * 
                 */
                int Hradius;

                /**
                 * @brief the vertical radius of the particle
                 * 
                 */
                int Vradius;

                /**
                 * @brief if true, it will draw filled ellipse, empty if not
                 * 
                 */
                bool filled;
            };

            /**
             * @brief the style of the particle
             * 
             */
            union Particle_style{
                Particle_Circle circle;
                Particle_Square square;
                Particle_Ellipse ellipse;
                Particle_Point point;
            };

            enum Particle_Style{
                Particle_circle,
                Particle_square,
                Particle_ellipse,
                Particle_point
            };

            /**
             * @brief the degraded
             * 
             */
            struct Degraded{
                /**
                 * @brief the starting color
                 * 
                 */
                SDL_Color sColor;

                /**
                 * @brief the ending color
                 * 
                 */
                SDL_Color eColor;
            };
            
            /**
             * @brief Set the Color of the particul effect
             * 
             * @param sColor the starting color
             * @param eColor the ending color
             */
            void setColor(SDL_Color sColor, SDL_Color eColor);

            /**
             * @brief Set the starting color
             * 
             * @param color the color (rgba)
             */
            void setStartingColor(SDL_Color color);

            /**
             * @brief set the ending color
             * 
             * @param color the color (rgba)
             */
            void setEndingColor(SDL_Color color);

            /**
             * @brief set the time of the particle
             * 
             * @param time the time
             */
            void setTime(int time);

            /**
             * @brief get the time of the particle
             * 
             * @return return the time
             */
            int getTime(void);

            /**
             * @brief set the strength of parcticules
             * 
             * @param strength the new strength
             */
            void setStrength(float strength);
            
            /**
             * @brief get the strength of the particles
             * 
             * @return return the srtength
             */
            float getStrength(void);

            /**
             * @brief print animation parameters into the the termial
             * 
             */
            void print(void);

            /**
             * @brief get the light name of the type, null if there is not light effect
             * 
             * @return return the name of the light
             */
            string getLight(void);

            /**
             * @brief get the name of the particle
             * 
             * @return return the name
             */
            string getName(void);

            /**
             * @brief get the style type of the particle animation
             * 
             * @return retrun the particle animation
             */
            Particle_Style getStyle(void);

            /**
             * @brief get the style struct of the particle animation
             * 
             * @return return the particle animation struct
             */
            Particle_style* getStyleType(void);

            /**
             * @brief get the particle color at the start
             * 
             * @return return a color 
             */
            SDL_Color getStartColor(void);

            /**
             * @brief get the particle color at the end
             * 
             * @return retur a color 
             */
            SDL_Color getEndColor(void);

            /**
             * @brief get the density of the particle type
             * 
             * @return return an int
             */
            int getDensity(void);

        private:
            /**
             * @brief the name of the animation
             * 
             */
            string name;

            /**
             * @brief the color of particules
             * 
             */
            Degraded color;

            /**
             * @brief the style of the particle
             * 
             */
            Particle_style style;

            /**
             * @brief the type of style
             * 
             */
            Particle_Style style_type;

            /**
             * @brief the time for every particles
             * 
             */
            int point_time;

            /**
             * @brief the strength of particules
             * 
             */
            float particule_strength;

            /**
             * @brief the delay between every particle push
             * 
             */
            int density;

            /**
             * @brief light name, empty if there is not effect
             * 
             */
           string light;

            /**
             * @brief set the type of the animation
             * 
             */
            void setCircle(void);
            void setPoint(void);
            void setSquare(void);
            void setEllipse(void);

    };

    bool operator==(Particles_type* type, string name);

    /**
     * @brief push a new particle type from a xml node
     * 
     * @param node the xml node
     */
    void pushParticle_type(XMLNode* node);
    
    /**
     * @brief search in every particles type
     * 
     * @param name the name
     * @return return the type if found, NULL if not found
     */
    Particles_type* searchParticle(string name);

    void clear_particlesType(void);

#endif