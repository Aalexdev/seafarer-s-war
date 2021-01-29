#ifndef __SAVE__
#define __SAVE__

    #include <iostream>
    #include <cstring>
    using namespace std;
    
    #include "api/io/xml.hpp"
    #include "ui/widgets/button.hpp"

    class Save{
        public:
            Save();
            ~Save();

            bool load_from_xml(XMLNode* node);
            bool load(void);

            std::string* getName(void){return &this->name;}
            void setName(std::string name){this->name = name;}

            std::string getPath(void){return this->file_path;}
        
        private:
            std::string name;
            std::string file_path;
    };

    class Savelist{
        public:
            Savelist();
            ~Savelist();

            bool load_from_xml(XMLNode* node);

            bool draw(void);
            bool update(void);
        
        private:
            vector<Save*> saves;

            vector<TextButton*> buttons;
            vector<Text*> texts;
    };

#endif