#ifndef __MUNITION__
#define __MUNITION__

    #include <iostream>
    #include <SDL2/SDL.h>

    using namespace std;

    class Ammunition_type;
    class Ammunition;

    #include "api/io/xml.hpp"
    #include "api/class/entity.hpp"
    #include "ui/graphics/sprite.hpp"

    class Ammunition_type{
        public:
            Ammunition_type();
            ~Ammunition_type();

            /**
             * @brief load the type from a xml node
             * 
             * @param node the xml node
             * @return return true if load, false on error
             */
            bool loadFrom_XML(XMLNode* node);

            /**
             * @brief get the texture of the ammunition type
             * 
             * @return return the texture
             */
            SDL_Texture* getTexture(void);

            /**
             * @brief the light structure
             * 
             * /!\ soon 
             */
            struct Light{
                
                /**
                 * @brief the strength of the light effect
                 * 
                 */
                int strength;

                /**
                 * @brief color of the light
                 * 
                 */
                int r, g, b;
            };

            /**
             * @brief get the name of teh ammunition
             * 
             * @return return the name 
             */
            string getName(void);

            /**
             * @brief get the type of the ammunition
             * 
             * @return return the type
             */
            string getType(void);

            /**
             * @brief get the size of the texture
             * 
             * @return return a rect
             */
            SDL_Rect getSize(void);

            /**
             * @brief get the initial speed
             * 
             * @return int 
             */
            int getInitialSpeed(void);

            /**
             * @brief get the light of the amunition
             * 
             * @return Light* 
             */
            Light* getLight(void);

            /**
             * @brief Get the Damages object
             * 
             * @return int 
             */
            int getDamages(void);

        private:
            string name;

            /**
             * @brief a type name, used to select a from equipment
             * 
             */
            string type;

            /**
             * @brief the texture of the ammunition
             * 
             */
            SDL_Texture* texture;

            /**
             * @brief the rect of the ammunition's texture
             * 
             */
            SDL_Rect rect;

            /**
             * @brief damages of the ammunition
             * 
             */
            int damages;

            /**
             * @brief the speed at the ouput of the cannon
             * 
             */
            int initialSpeed;

            /**
             * @brief the light emmeted by the ammunition
             * 
             */
            Light* light;
    };

    class Ammunition{
        public:
            /**
             * @brief Construct a new Ammunition object
             * 
             */
            Ammunition(Entity* parent);

            /**
             * @brief Construct a new Ammunition object
             * 
             * @param angle the angle of the ammunition
             */
            Ammunition(Entity* parent, int angle, int x, int y);

            /**
             * @brief Destroy the Ammunition object
             * 
             */
            ~Ammunition();

            /**
             * @brief load type the ammunition from a type name
             * 
             * @param type_name the name of the type
             * @return return true if loaded, false on error
             */
            bool load(string type_name);

            /**
             * @brief update the ammunition vars and collisions
             * 
             */
            bool update(void);

            /**
             * @brief draw the ammunition on the screen
             * 
             * @return return true if drawn, false on error
             */
            bool draw(void);

            /**
             * @brief get if the ammunition is linked with a type
             * 
             * @return return true if linked, false otherwise 
             */
            bool linked(void);

            /**
             * @brief draw the light effect (if activ)
             * 
             */
            void drawLight(void);

            /**
             * @brief return true if the ammunition should be deleted
             * 
             * @return true 
             * @return false 
             */
            bool is_delete(void);   
        
        private:
            /**
             * @brief the ârent of the ammunition
             * 
             */
            Entity* parent;

            /**
             * @brief the type of the ammunition
             * 
             */
            Ammunition_type* type;

            /**
             * @brief the vector of the ammunition
             * 
             */
            int angle;

            /**
             * @brief the actual speed of the ammunition
             * 
             */
            int speed;

            /**
             * @brief the rectangle of the ammunition
             * 
             */
            SDL_Rect rect;

            /**
             * @brief delete linked value with the type
             * 
             */
            void unlink(void);

            /**
             * @brief the point where the ammunition was launched
             * 
             */
            SDL_Point spoint;


            int getX(void);

            int getY(void);

            /**
             * @brief 
             * 
             */
            bool should_delete;

    };
    
    /**
     * @brief return ammuniation type with the input name
     * 
     * @param name searching name
     * @return return the founded ammunition, NULL if not exist 
     */
    Ammunition_type* find(string name);
    
    /**
     * @brief get a vector filled of every ammunition types with the input type
     * 
     * @param type the searching type
     * @return vector<Ammunition_type*> 
     */
    vector<Ammunition_type*> searchType(string type);

    /**
     * @brief get if the input type is used by a ammunition type
     * 
     * @param type the 
     * @return return true if used, false otherwise
     */
    bool existingType(string type);

#endif