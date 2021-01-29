/* 
 * debug.hpp by Aalex
 * 
 * content:
 *  DebugText class
 *  DebugMenu class
*/

#ifndef __DEBUG__
#define __DEBUG__

    #include <iostream>
    #include <vector>
    #include <SDL2/SDL.h>

    using namespace std;

    #include "ui/widgets/text.hpp"

    class DebugText : public Text{
        public:
            DebugText();
            ~DebugText();
            
            bool bind(int *value);
            bool setPrefix(std::string prefix);

            bool update(void);
        
        private:
            int* value;
            int valueBuf;
            std::string prefix;
    };

    class DebugMenu{
        public:
            DebugMenu();
            ~DebugMenu();

            void append(DebugText* text);
            bool draw(void);

        private:
            vector<DebugText>* texts;

    };

#endif