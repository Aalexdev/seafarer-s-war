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

    class BoatPart : public Hitbox{
        public:
            ~BoatPart();
            BoatPart();

            int health;
            int maxHealth;
            std::string name;
    };

    class Entity_type{
        public:
            Entity_type();
            ~Entity_type();

            bool load_from_xml(XMLNode* node);
            std::string get_name(void){return this->name;}

            SDL_Texture* getTexture(void){return this->texture;}
            vector<BoatPart*> getParts(void);
            SDL_Rect getRect(void){return this->rect;}

            int getMaxSpeed(void){return this->maxSpeed;}
            int getMaxRotationnalSpeed(void){return this->maxRotationnalSpeed;}
            int getSpeedDelay(void){return this->speedDelay;}
            int getRotationalDelay(void){return this->rotationalDelay;}

        private:
            std::string name;

            SDL_Texture* texture;
            SDL_Rect rect;

            // perform
            int maxSpeed;
            int maxRotationnalSpeed;

            int speedDelay;
            int rotationalDelay;

            vector<BoatPart*> parts;

            // layers
            int layerMax, layerMin;
            bool used_name(std::string name);
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

        private:

            Entity_type* type;

            int angle;
            int speed;
            int turnSpeed;
            int z;

            // ticks
            int speedTicks;
            int turnTicks;
            SDL_Rect rect;

            vector<BoatPart*> parts;

            Team* team;
            bool is_player;
    };

#endif