#ifndef __BUTTON__
#define __BUTTON__

    #include "ui/graphics/sprite.hpp"
    #include "ui/widgets/text.hpp"
    #include "api/io/xml.hpp"
    #include "ui/graphics/sprite.hpp"

    enum ButtonState{
        ButtonNone = 0,
        ButtonHover = 1,
        ButtonPush = 2
    };

    class ButtonClass{
        public:
            ButtonClass(){}
            ~ButtonClass(){}

            bool exec(void);
            ButtonState state;
            string cmd;
    };

    class TextButton : public Text, private ButtonClass{
        public:
            TextButton(){}
            ~TextButton(){}

            // only of mouseMotion
            void update(void);
            bool read_from_xml(XMLNode* node);
    };

    class ImageButton : private ButtonClass{
        public:
            ImageButton(){}
            ~ImageButton(){}

            // only if mouseMotion
            void update(void);
            bool read_from_xml(XMLNode* node);
            bool draw(void);
        
        private:
            SDL_Texture* texture;
            SDL_Rect rect;
    };

    class SpriteButton : public Sprite, private ButtonClass{
        public:
            SpriteButton(){}
            ~SpriteButton(){}

            // if None draw 0, if Hover draw entier animation
            bool drawButton(void);
            void update(void);
            bool read_from_xml(XMLNode* node);
    };

#endif