#ifndef __ANIMATION__
#define __ANIMATION__

    #include <iostream>
    #include <vector>
    #include <string>

    #include "api/io/xml.hpp"
    #include "api/functions/math.hpp"
    #include "ui/graphics/light.hpp"

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

#endif