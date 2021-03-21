/**
 * @file layer.hpp
 * @author @Aalexdev (aaleex394@gmail.com)
 * @brief layers file
 * @version 1.0.1
 * 
 * @copyright (c) 2021 Aalex
 * 
 * MIT License
 *
 *  Copyright (c) 2021 Aalex
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions: 
 * 
 * The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#ifndef __LAYER__
#define __LAYER__

    #include <iostream>
    #include <SDL2/SDL.h>
    #include <vector>

    using namespace std;

    #include "ui/graphics/sprite.hpp"
    
    /**
     * @brief the texture in the layer
     * 
     */
    class LayerTexture{
        public:
            /**
             * @brief Construct a new Layer Texture object
             * 
             */
            LayerTexture();

            /**
             * @brief Destroy the Layer Texture object
             * 
             */
            ~LayerTexture();

            /**
             * @brief draw the layer on the renderer
             * 
             * @return retunr true if drawn, false on error
             */
            bool draw(void);

            /**
             * @brief the texture
             * 
             */
            SDL_Texture* texture;

            /**
             * @brief the size of the texture
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the alpha canal of the texture
             * 
             */
            Uint8 alpha;

            /**
             * @brief the additionnal position of the texture
             * 
             */
            SDL_Point addingPos;
    };
    
    /**
     * @brief layer class
     * 
     */
    class Layer{
        public:
            /**
             * @brief Construct a new Layer object
             * 
             */
            Layer(void);

            /**
             * @brief Destroy the Layer object
             * 
             */
            ~Layer();

            /**
             * @brief load the layer from a XML node
             * 
             * @param node the xml node
             * @return return true if loaded, false on error
             */
            bool read_from_xml(XMLNode* node);

            /**
             * @brief draw the layer on the renderer
             * 
             * @return return true if drawn, false on errro
             */
            bool draw(void);

            /**
             * @brief get the Z axis
             * 
             * @return return the z axis
             */
            int getZ(void){return this->z;}
        
        private:
            /**
             * @brief the layer's name, usde to locate
             * 
             */
            string name;

            /**
             * @brief textures of the layer
             * 
             */
            vector<LayerTexture*> textures;

            /**
             * @brief the position of textures
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the angle of the layer
             * 
             */
            int angle;

            /**
             * @brief the speed, in px per sec
             * 
             */
            int speed;

            /**
             * @brief the additionnal position of the layer
             * 
             */
            int addX, addY;

            /**
             * @brief the starting point of the layer
             * 
             */
            SDL_Point startingPos;


            /**
             * @brief the height of the layer
             * 
             */
            int z;

            /**
             * @brief the timer
             * 
             */
            int timer;

            /**
             * @brief the delay between every additionnal pos
             * 
             */
            int delay;

    };

#endif