/*
 * sprite.hpp by Aalex
 * 
 * content:
 *  the type of a sprite
 *  Sprite_type class
 * 
 *  parts of a sprite
 *  Sprite_child class
 * 
 *  a list of Spryte_type
 *  Sprite_list class
 * 
 *  a prite to connect with a Sprite_type
 *  Sprite class
*/

#ifndef __SPRITE__
#define __SPRITE__

    #include <iostream>
    #include <cstring>
    #include <SDL2/SDL.h>
    #include <vector>

    using namespace std;

    #include "api/functions/texture.hpp"
    #include "api/io/xml.hpp"

    class Sprite_child{
        public:
            Sprite_child(){}
            Sprite_child(SDL_Rect rect) : rect(rect){}
            ~Sprite_child(){}

            void setRect(SDL_Rect new_rect){this->rect = new_rect;}
            SDL_Rect getRect(void){return this->rect;}

            int getX(void){return this->rect.x;}
            int getY(void){return this->rect.y;}
            int getW(void){return this->rect.w;}
            int getH(void){return this->rect.h;}

            void setX(int new_x){this->rect.x = new_x;}
            void setY(int new_y){this->rect.y = new_y;}
            void setW(int new_w){this->rect.w = new_w;}
            void setH(int new_h){this->rect.h = new_h;}

        private:
            SDL_Rect rect;
    };

    class Sprite_type{
        public:
            Sprite_type();
            ~Sprite_type();

            const bool is_loaded(void) const {return this->isLoaded;}

            bool load_from_xml(XMLNode* node);
            bool reload(void);

            const string getName(void) const {return this->name;}
            const int get_id(void) const {return this->id;}

            SDL_Rect getIndex(int index);
            int getSize(void){return this->children.size();}

            SDL_Texture *getTexture(void){return this->sprite;}

        private:
            // destination rect
            SDL_Rect dstRect;

            // the textrue of the sprire
            SDL_Texture* sprite;

            //differents parts of the sprite
            vector<Sprite_child*> children;

            // if the sprite is loaded
            bool isLoaded;

            // the id of the sprite type
            int id;

            // the name of the sprite
            string name;

            // the lenght if the sprite
            int lenght;

            // the size of sprites children
            int width, height;
    };

    class Sprite;

    class Sprite_list{
        public:
            Sprite_list(){}
            ~Sprite_list(){for (Sprite_type* type : this->children){if (type) delete type;}}

            bool read_from_xml(XMLNode* node);

            Sprite_type* search(string name);
            Sprite_type* search(int id);
        
        private:
            vector<Sprite_type*> children;

    };

    class Sprite{
        public:
            Sprite(Sprite_list* list);
            Sprite();
            ~Sprite();

            void setList(Sprite_list* list);
            
            bool set(int id);
            bool set(string name);
            void set(Sprite_type* type);

            Sprite_type* get_type(void);
            int get_id(void);
            string get_name(void);

            void setRect(SDL_Rect new_rect){this->rect = new_rect;}
            SDL_Rect getRect(void){return this->rect;}

            void setPos(int x, int y){this->rect.x = x; this->rect.y = y;}
            void setSize(int w, int h){this->rect.h = h; this->rect.w = w;}

            int getX(void){return this->rect.x;}
            int getY(void){return this->rect.y;}
            int getW(void){return this->rect.w;}
            int getH(void){return this->rect.h;}

            void setX(int x){this->rect.x = x;}
            void setY(int y){this->rect.y = y;}
            void setW(int w){this->rect.w = w;}
            void setH(int h){this->rect.h = h;}

            bool draw(void);
            void set_duration(int new_duration){this->duration = new_duration;}
            const int get_duration(void) const {return this->duration;} 

            void setAngle(int new_angle){this->angle = new_angle;}
            int getAngle(void){return this->angle;}

            bool is_Init(void);
            void setIndex(int new_index){this->index = new_index;}
            const int get_index(void) const {return this->index;}

            void set_update(bool new_update){this->update = new_update;}
            bool is_updating(void){return this->update;}

            bool read_from_xml(XMLNode* node);
            
        private:
            Sprite_list* list;
            Sprite_type* type;

            SDL_Rect rect;
            int index;
            
            // time
            long ticks;
            int duration;
            int angle;
            bool update;
    };

#endif