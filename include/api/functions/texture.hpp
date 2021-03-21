#ifndef __TEXTURE__
#define __TEXTURE__

    #include <SDL2/SDL.h>
    #include <iostream>
    using namespace std;

    #include "api/io/xml.hpp"

    /**
     * @brief load a texture from a path, set the size of the image into the rect
     * 
     * @param path the image's path
     * @param rect the size of the image
     * @return return the texture, NULL on error
     */
    SDL_Texture* loadTexture(string path, SDL_Rect *rect);

    /**
     * @brief transform a surface into a texture
     * 
     * @param surface the source surface
     * @param rect the size of the texture
     * @return return the texture, NULL on error
     */
    SDL_Texture* surfaceToTexture(SDL_Surface *surface, SDL_Rect *rect);

    /**
     * @brief create a RGBA texture from the input color and of the size of the rect
     * 
     * @param color the color of the textuire
     * @param rect the szie of the texture
     * @return return the textrue of created, false on error
     */
    SDL_Texture* createRGBTexture(SDL_Color color, SDL_Rect rect);
    
    /**
     * @brief the image class
     * 
     */
    class Image{
        public:
            /**
             * @brief Construct a new Image object
             * 
             * @param path the image's path
             */
            Image(string path);

            /**
             * @brief Construct a new Image object, create a RGBA image
             * 
             * @param color the color
             */
            Image(SDL_Color color);

            /**
             * @brief Construct a new Image object, create a RGBA image
             * 
             * @param r red
             * @param g green
             * @param b blue
             */
            Image(Uint8 r, Uint8 g, Uint8 b);

            /**
             * @brief Construct a new Image object
             * 
             */
            Image(){}

            /**
             * @brief Destroy the Image object
             * 
             */
            ~Image();

            /**
             * @brief set the size of the image
             * 
             * @param new_rect the new rectange 
             */
            void setRect(SDL_Rect new_rect){this->rect = new_rect;}

            /**
             * @brief set the position of the image
             * 
             * @param x x axis
             * @param y y axis
             */
            void setPos(int x, int y){this->rect.x = x; this->rect.y = y;}

            /**
             * @brief set the x axis
             * 
             * @param x x axis
             */
            void setX(int x){this->rect.x;}


            /**
             * @brief set the y axis
             * 
             * @param y y axis
             */
            void setY(int y){this->rect.y;}

            /**
             * @brief set the image's size
             * 
             * @param w width of the image
             * @param h height of the image
             */
            void setSize(int w, int h){this->rect.w; this->rect.h = h;}

            /**
             * @brief set the width of the image
             * 
             * @param w width of the image
             */
            void setW(int w){this->rect.w = w;}

            /**
             * @brief set the height of the image
             * 
             * @param h height of the image
             */
            void setH(int h){this->rect.h = h;}

            /**
             * @brief set the position of the image into x and y
             * 
             * @param x the pointer to the x destination
             * @param y the pointer to the y destination
             */
            void getPos(int *x, int *y){x = &this->rect.x; y = &this->rect.y;}

            /**
             * @brief get the x axis
             * 
             * @return return the x of the rectangle
             */
            int getX(void){return this->rect.x;}

            /**
             * @brief get the y axis
             * 
             * @return return the y axis of the rectangle
             */
            int getY(void){return this->rect.y;}

            /**
             * @brief get the size of the image into x and h
             * 
             * @param w the destination width point
             * @param h the destination heigth point
             */
            void getSize(int *w, int *h){w = &this->rect.w; h = &this->rect.h;}

            /**
             * @brief get the width of the image
             * 
             * @return return the width of the rect
             */
            int getW(void){return this->rect.w;}

            /**
             * @brief gte the height of the image
             * 
             * @return return the height of the rect
             */
            int getH(void){return this->rect.h;}

            /**
             * @brief get a pointer to the image's rect
             * 
             * @return return the image's rect 
             */
            SDL_Rect* getRect(void) {return &this->rect;}

            /**
             * @brief set the image from an image path
             * 
             * @param path the path to the image source
             * @return return true if loaded, false on error 
             */
            bool set(string path);

            /**
             * @brief set the image from a color
             * 
             * @param color the color
             * @return return if created, false on error
             */
            bool set(SDL_Color color);

            /**
             * @brief set the image from color
             * 
             * @param r red canal
             * @param g green canal
             * @param b blue canal
             * @return return true if created, false on error 
             */
            bool set(Uint8 r, Uint8 g, Uint8 b);

            /**
             * @brief set the alpha canal of the image
             * 
             * @param alpha the alpha canal
             * @return retunr true on succes, false on error
             */
            bool setAlpha(Uint8 alpha);

            /**
             * @brief draw the image on the renderer
             * 
             * @return return true if drawn, false on error
             */
            bool draw(void);

            /**
             * @brief load the image from a xml node
             * 
             * @param node the xml node
             * @return retrun true if loaded, false on error
             */
            bool read_from_xml(XMLNode* node);

        private:
            /**
             * @brief the size and the position of the image
             * 
             */
            SDL_Rect rect;

            /**
             * @brief the SDL texture of the image
             * 
             */
            SDL_Texture* texture;
    };

#endif