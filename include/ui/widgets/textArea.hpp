#ifndef _TEXTAREA_H_
#define _TEXTAREA_H_

    #include <iostream>
    #include <cstring>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

    #include "api/functions/texture.hpp"
    #include "ui/widgets/text.hpp"
    #include "api/io/xml.hpp"

    /* structs */

    class TextArea {
        public:
            TextArea();
            ~TextArea();
            bool setBackground(string path);
            bool setBackground(Uint8 r, Uint8 g, Uint8 b);

            void setPos(int x, int y);
            void setSize(int w, int h);
            void setRect(SDL_Rect rect);

            void setX(int x);
            void setY(int y);
            void setW(int w);
            void setH(int h);

            void lock(void);
            void unlock(void);

            void setMaxText(int maxSize);

            bool draw(void);
            void update(void);
            void event(SDL_Event* e);

            bool read_from_xml(XMLNode* node);

            string getTag(void);
            string getText(void);

        private:
            Image* background;
            Text* text;
            bool locked;

            int maxSize;
            bool write;
            Uint8 alpha;

            string tag;
    };

#endif
