#ifndef __KEYPAD__
#define __KEYPAD__

    #include <iostream>
    #include <cstring>
    #include <vector>
    #include <SDL2/SDL.h>

    using namespace std;

    #include "api/io/xml.hpp"

    enum KeyType{
        Tkey,
        TkeyUp,
        TkeyDown
    };

    class Key{
        public:
            Key();
            ~Key();

            void setScancode(SDL_Scancode scancode);
            void setTag(std::string tag);
            void setCommand(std::string cmd);
            SDL_Scancode getScancode(void);
            void setType(KeyType type);

            void update(void);
            bool is_empty(void);

            bool get_message(std::string message);

        private:
            std::string cmd;
            std::string tag;
            std::string message;
            SDL_Scancode code;
            KeyType type;
            bool state;
            int messageId;

            void exec(void);

    };

    class Keypad{
        public:
            Keypad();
            ~Keypad();

            bool getKey(SDL_Scancode key);
            bool getKeyUp(SDL_Scancode key);
            bool getKeyDown(SDL_Scancode key);

            void event(SDL_Event e);
            bool read_xml(XMLNode* node);
        
        private:
            bool key[UINT8_MAX];
            bool keyUp[UINT8_MAX];
            bool keyDown[UINT8_MAX];

            vector<Key*> keys;

            bool used_key(SDL_Scancode scancode);
            Key* getFromScancode(SDL_Scancode scancode);
    };

#endif