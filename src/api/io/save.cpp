#include "api/io/save.hpp"
#include "main.hpp"

Save::Save(){
    if (IS_LOG_OPEN) LOG << "Save::save()" << endl;
}

Save::~Save(){
    this->file_path.clear();
    this->name.clear();
}

bool Save::load_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Save::load_from_xml" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Save::load_from_xml, reason : cannot load a save from a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            this->name = attr.value;
        } else if (!strcmp(attr.key, "file")){
            this->file_path = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNIG :: Save::load_from_xml, reason : cannot reconize '" << attr.key << "' save attribute" << endl;
        }
    }

    if (this->name.empty()){
        this->name = "Uncknow";
        if (IS_ERR_OPEN) ERR << "WARNING :: Save::load_from_xml, reason : the save has no name" << endl;
    }

    return true;
}

bool Save::load(void){
    return readXML(this->file_path, false);
}

Savelist::Savelist(){
    if (IS_LOG_OPEN) LOG << "Savelist::Savelist()" << endl;
}
Savelist::~Savelist(){
    for (Text* text :  this->texts){
        delete text;
    }
    this->texts.clear();

    for (TextButton* btn : this->buttons){
        delete btn;
    }
    this->buttons.clear();

    for (Save* save : this->saves){
        delete save;
    }
    this->saves.clear();
}

bool Savelist::load_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Savelist::load_from_xml" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Savelist::load_from_xml, reason : cannot load a save from a null node" << endl;
        return false;
    }

    for (int s=0; s<node->children.size; s++){
        XMLNode* saveNode = XMLNode_child(node, s);

        Save* save = new Save();

        if (save->load_from_xml(saveNode)){
            this->saves.push_back(save);
        } else {
            delete save;
        }
    }

    return true;
}

bool Savelist::draw(void);
bool Savelist::update(void);