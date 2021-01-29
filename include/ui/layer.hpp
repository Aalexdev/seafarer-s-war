#ifndef __LAYER__
#define __LAYER__

    #include <iostream>
    #include <SDL2/SDL.h>
    #include <vector>

    using namespace std;

    #include "ui/graphics/sprite.hpp"

    class LayerTexture{
        public:
            LayerTexture();
            ~LayerTexture();

            bool draw(void);

            SDL_Texture* texture;
            SDL_Rect rect;
            Uint8 alpha;
            SDL_Point addingPos;
    };

    class Layer{
        public:
            Layer(void);
            ~Layer();

            bool read_from_xml(XMLNode* node);

            bool draw(void);
            int getZ(void){return this->z;}
        
        private:
            vector<LayerTexture*> textures;
            SDL_Rect rect;

            int angle;
            int speed;

            int addX, addY;
            SDL_Point startingPos;

            std::string name;
            int id;

            // the height of the layer
            int z;

            long timer;
            int delay;

    };

#endif