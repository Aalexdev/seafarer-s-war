#ifndef __ENTITY__
#define __ENTITY__

    #include <iostream>
    #include <vector>
    #include <cstring>
    #include <SDL2/SDL.h>

    using namespace std;

    #include "api/io/xml.hpp"
    #include "api/functions/texture.hpp"
    #include "api/class/hitbox.hpp"

    class Team{
        public:
            Team();
            ~Team();

            bool load_from_xml(XMLNode* node);
            
            std::string getName(void){return this->name;}
            void setName(std::string new_name){this->name = new_name;}

            int getId(void){return this->id;}
            void setId(int new_id){this->id = new_id;}
        
        private:
            std::string name;
            int id;
    };

    class Part_type{
        public:
            Part_type();
            ~Part_type();

            void setName(std::string new_name){this->name = new_name;}
            bool read_from_xml(XMLNode* node);

            vector<HitPoint*> getPoints(void){return this->hitPoints;}
            int getMax_health(void){return this->maxHealth;}

            std::string getName(void){return this->name;}
        
        private:
            std::string name;
            vector<HitPoint*> hitPoints;

            int maxHealth;
    };

    class Part_Type_list{
        public:
            Part_Type_list();
            ~Part_Type_list();

            Part_type* search(std::string name);

            void push(Part_type* type);
            void pop(void);

            vector<Part_type*>* getVector(void){return &this->types;}
        
        private:
            vector<Part_type*> types;
    };

    class Part{
        public:
            Part();
            ~Part();

        private:
            Part_type* type;
    };

    class Entity_type{
        public:
            Entity_type();
            ~Entity_type();

            bool load_from_xml(XMLNode* node);
            std::string get_name(void){return this->name;}

            SDL_Texture* getTexture(void){return this->texture;}
            SDL_Rect getRect(void){return this->rect;}

            float getMass(void){return this->mass;}
            float getStrength(void){return this->strength;}

            int getLayerMin(void){return this->layerMin;}
            int getLayerMax(void){return this->layerMax;}
            int getMaxSpeed(void){return this->maxSpeed;}
            int getMinSpeed(void){return this->minSpeed;}

        private:
            std::string name;

            SDL_Texture* texture;
            SDL_Rect rect;

            // perform

            int speedDelay;
            int rotationalDelay;

            int speedAcceleration, turnAcceleration;

            // layers
            int layerMax, layerMin;
            int maxSpeed, minSpeed;
            bool used_name(std::string name);

            int maxHealth;
            
            float mass;
            float strength;
    };

    class Entity{
        public:
            Entity();
            Entity(bool isPlayer);
            ~Entity();

            bool set(std::string name);

            void update(void);
            bool draw(void);

            int getZ(void){return this->z;}
            int getX(void){return this->rect.x;}
            int getY(void){return this->rect.y;}
            int getW(void){return this->rect.w;}
            int getH(void){return this->rect.h;}

            bool load_from_xml(XMLNode* node);

            bool is_linked(void){return this->type;}
            void unlink(void);

            int maxHealth;

        private:

            Entity_type* type;

            float angle;
            float z;

            SDL_Rect rect;

            int health;

            Team* team;
            bool is_player;

            vector<HitPoint*> hitPoints;

            float acceleration;
            float speed;
            float strength;

            float turn_acceleration;
            float turn_speed;
            float turn_strength;

            bool is_mouving, is_turn;
            int mouving_ticks, turn_ticks;

            void reset(void);
    };

#endif