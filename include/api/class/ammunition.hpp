#ifndef __AMMUNITION__
#define __AMMUNITION__

    class Ammunition;

    #include "api/types/Ammunition_type.hpp"

    #define AMMUNITION_MAX_DIST 3000

    class Ammunition{
        public:
            /**
             * @brief Construct a new Ammunition object
             * 
             */
            Ammunition();

            /**
             * @brief Destroy the Ammunition object
             * 
             */
            ~Ammunition();
        
            /**
             * @brief set the ammunition's type from a name
             * 
             * @param name the ammunition_type's name
             * @return return true if loaded, false on error 
             */
            bool set(string name);

            /**
             * @brief set the ammunition's type from an id
             * 
             * @param id the ammunition_typs's id
             * @return retunr true if loaded, false on error
             */
            bool set(int id);

            /**
             * @brief set the ammunition's type from a ammunitionètype pointer
             * 
             * @param type the type
             */
            void set(Ammunition_type* type);
            
            /**
             * @brief if the ammunition is linked with a type
             * 
             * @return retunr true if linked, false if not
             */
            bool linked(void);

            /**
             * @brief get the speed of the ammunition
             * 
             * @return float 
             */
            float speed(void);

            /**
             * @brief set the speed of the ammunition
             * 
             * @param speed the new speed of the ammunition
             */
            void speed(float speed);

            /**
             * @brief update the speed of the ammunition
             * 
             */
            void update_speed(void);

            /**
             * @brief update the position of the ammunition
             * 
             */
            void update_pos(void);

            /**
             * @brief update the collision if the ammunition with entitys
             * 
             */
            void update_collisions(void);

            /**
             * @brief get the angle of the ammunition
             * 
             * @return int 
             */
            int angle(void);

            /**
             * @brief set the angle of the ammunition
             * 
             * @param angle the new angle of the ammunition
             */
            void angle(int angle);

            /**
             * @brief get the type of the ammunition
             * 
             * @return Ammunition_type* 
             */
            Ammunition_type* type(void);

            /**
             * @brief put type attributes into the ammunition
             * 
             */
            void get_type_attributes(void);

            /**
             * @brief get the ammunition's rect
             * 
             * @return SDL_Rect 
             */
            SDL_Rect rect(void);

            /**
             * @brief get a pointer to the ammunition's rect
             * 
             * @return SDL_Rect* 
             */
            SDL_Rect* rect_ptr(void);

            /**
             * @brief get the distance made by the ammunition
             * 
             * @return float 
             */
            float dist(void);

            /**
             * @brief set the diance
             * 
             * @param dist the new distance
             */
            void dist(float dist);

            /**
             * @brief get the strength of the ammunition
             * 
             * @return float 
             */
            float strength(void);

            /**
             * @brief set the strength of the ammunition
             * 
             * @param strength the new strength
             */
            void strength(float strength);

            /**
             * @brief get the mass of the ammunition
             * 
             * @return float 
             */
            float mass(void);

            /**
             * @brief set the mass of the ammunition
             * 
             * @param mass the new mass
             */
            void mass(float mass);

            /**
             * @brief get if the ammunition should be delete
             * 
             * @return return trus if it is, false if not
             */
            bool should_delete(void);

            /**
             * @brief get the X axis of the ammunition, on the map
             * 
             * @return int 
             */
            int x(void);

            /**
             * @brief get the Y axis of the ammunition, on the map
             * 
             * @return int 
             */
            int y(void);

            /**
             * @brief get the Z axis of the ammunition
             * 
             * @return int 
             */
            float z(void);

            /**
             * @brief set the X axis
             * 
             * @param x the new x
             */
            void x(int x);

            /**
             * @brief set the Y axis
             * 
             * @param y the new y
             */
            void y(int y);

            /**
             * @brief set the z value
             * 
             * @param z the new z
             */
            void z(float z);

            /**
             * @brief draw the ammunition type's texture on the renderer
             * 
             * @return return true if drawn, false on error
             */
            bool draw(void);

            /**
             * @brief delete the ammunition and erease it from the amminition list
             * 
             */
            void pop(void);

        private:
            /**
             * @brief the type if the ammunition
             * 
             */
            Ammunition_type* _type;

            /**
             * @brief the speed of the ammunition, decrease in the time (in px per ms)
             * 
             */
            float _speed;

            /**
             * @brief the strength of the ammunition
             * 
             */
            float _strength;

            /**
             * @brief the mass of the ammunition
             * 
             */
            float _mass;

            /**
             * @brief the actual angle of the ammunition
             * 
             */
            int _angle;

            /**
             * @brief the targeting layer
             * 
             */
            int _layer_target;

            /**
             * @brief the up/down speed
             * 
             */
            float _up_down_speed;

            /**
             * @brief store the position and the size of the ammunition
             * 
             */
            SDL_Rect _rect;

            /**
             * @brief the distance made by the ammunition from the lauching
             * 
             */
            float _dist;

            /**
             * @brief the z axis
             * 
             */
            float _z;

            /**
             * @brief the pop value, erease the ammunition whene it's true
             * 
             */
            bool _pop;

            /**
             * @brief the particle pointer
             * 
             */
            Particles* _particles;
    };

    Ammunition* operator<<(Ammunition& amm, string type_name);
    Ammunition* operator<<(Ammunition& amm, int type_id);
    Ammunition* operator<<(Ammunition& amm, Ammunition_type* type);

    bool operator==(Ammunition& amm, Ammunition_type* type);
    bool operator==(Ammunition& amm, string type_name);
    bool operator==(Ammunition& amm, int type_id);

    Ammunition* push_Ammunition(string name);

    int update_ammunitions(void* ptr);
    int draw_ammunitions(int z);
    void clear_ammunitions(void);

#endif