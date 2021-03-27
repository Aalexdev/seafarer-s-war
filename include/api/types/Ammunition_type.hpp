#ifndef __MUNITION__
#define __MUNITION__

    #include <iostream>
    #include <SDL2/SDL.h>

    using namespace std;

    class Ammunition;

    #include "api/io/xml.hpp"
    #include "ui/graphics/light.hpp"

    
    #ifndef AMMUNITION_TYPE_TARGET_NONE
        #define AMMUNITION_TYPE_TARGET_NONE 0
    #endif

    #ifndef AMMUNITION_TYPE_TARGET_LESS
        #define AMMUNITION_TYPE_TARGET_LESS 1
    #endif

    #ifndef AMMUNITION_TYPE_TARGET_EQUAL
        #define AMMUNITION_TYPE_TARGET_EQUAL 2
    #endif

    #ifndef AMMUNITION_TYPE_TARGET_GREATER
        #define AMMUNITION_TYPE_TARGET_GREATER 3
    #endif


    class Ammunition_type{
        public:
            /**
             * @brief Construct a new Ammunition_type object
             * 
             */
            Ammunition_type();

            /**
             * @brief Destroy the Ammunition_type object
             * 
             */
            ~Ammunition_type();

            /**
             * @brief load the node from a XML node
             * 
             * @param node the xml node
             * @return return true if loaded, false on error
             */
            bool load(XMLNode* node);

            /**
             * @brief get the name of the type
             * 
             * @return string 
             */
            string name(void);

            /**
             * @brief get the id of the type
             * 
             * @return int 
             */
            int id(void);

            /**
             * @brief get the texture of the Ammunition type. Use size() to get the size of the texture
             * 
             * @return SDL_Texture* 
             */
            SDL_Texture* texture(void);

            /**
             * @brief get the size of the texture
             * 
             * @return SDL_Rect 
             */
            SDL_Rect size(void);

            /**
             * @brief get a pointer to the size of the texture
             * 
             * @return SDL_Rect* 
             */
            SDL_Rect* size_ptr(void);

            /**
             * @brief get the speed if the ammunition, in px per milisecond
             * 
             * @return float 
             */
            float strength(void);

            /**
             * @brief get the texture's rotation center
             * 
             * @return SDL_Point 
             */
            SDL_Point center(void);

            /**
             * @brief get the pointer to the texture's rotation center
             * 
             * @return SDL_Point* 
             */
            SDL_Point* center_ptr(void);

            /**
             * @brief return the targeting layer (used for gravity or floating)
             * 
             * @return int 
             */
            int target_layer(void);

            /**
             * @brief get the layer_target_type member
             * 
             * @return Uint8 
             */
            Uint8 layer_target_type(void);

            /**
             * @brief get the up/down speed of the type
             * 
             * @return float 
             */
            float up_down_speed(void);

            /**
             * @brief set the id of the type
             * will not set the if id the id is early used by another ammunition_type
             * 
             * @param id the new id
             */
            void id(int id);

            /**
             * @brief set the name of the type
             * will not the name if another ammunition_type has the same name
             * 
             * @param name the new name
             */
            void name(string name);

            /**
             * @brief get the mass of the type
             * 
             * @return float 
             */
            float mass(void);

            /**
             * @brief set the mass of the type
             * 
             * @param mass the new mass
             */
            void mass(float mass);

            /**
             * @brief get the particle type's name
             * 
             * @return string 
             */
            string particles_type(void);

            /**
             * @brief set the particle type
             * 
             * @param type 
             */
            void particules_type(string type);

        private:
            /**
             * @brief the name of the type
             * 
             */
            string _name;

            /**
             * @brief the id of the type
             * 
             */
            int _id;

            /**
             * @brief the texture of the ammunition
             * 
             */
            SDL_Texture* _texture;

            /**
             * @brief the size of the Ammunition
             * 
             */
            SDL_Rect _size;

            /**
             * @brief the texture's rotation center
             * 
             */
            SDL_Point _center;

            /**
             * @brief the speed of the ammunition in px per milisecond
             * 
             */
            float _strength;

            /**
             * @brief the mass of the ammunition
             * 
             */
            float _mass;

            /**
             * @brief the targeting layer of the ammunition
             * 
             */
            int _layer_target;

            /**
             * @brief delete the ammunition if the layer_target is the same the the z ammunition memeber
             * 
             */
            Uint8 _layer_target_type;

            /**
             * @brief the speed of the up/down mouvement (layer per milisecond)
             * 
             */
            float _up_down_speed;

            /**
             * @brief the name of the particle type, empty if not effect
             * 
             */
            string _particle_type;
    };
    
    bool operator<<(Ammunition_type type, XMLNode* node);
    bool operator==(Ammunition_type type, string name);
    bool operator==(Ammunition_type type, int id);

    bool new_Ammunition_type(XMLNode* node);
    bool new_Ammunition_type(string file_path);

    Ammunition_type* search_Ammunition_type(string name);
    Ammunition_type* search_Ammunition_type(int id);

    void clear_Ammunition_type(void);

#endif