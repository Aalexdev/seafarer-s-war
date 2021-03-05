#include "api/class/island.hpp"
#include "main.hpp"

Island_type::Island_type(){
    if (IS_LOG_OPEN) LOG << "Island_type::Island_type()" << endl;
    this->texture = nullptr;
    this->rect = {0, 0, 0, 0};
}

Island_type::~Island_type(){
    if (IS_LOG_OPEN) LOG << "Island_type::~Island_type()" << endl;
    if (this->texture) SDL_DestroyTexture(this->texture);
    this->name.clear();
}

bool Island_type::load_from_xml(XMLNode* node){

    if (IS_LOG_OPEN) LOG << "Island_type::load_from_xml()" << endl;
    /*

    <island name="*name*">
        <image path="*path*"/>
    </island>

    */
    
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Island_type, reason : cannot load it from a null xml node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            this->name = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: island node, reason : cannot reconize '" << attr.key << "' island attribute" << endl;
        }
    }

    if (this->name.empty()){
        if (IS_ERR_OPEN) ERR << "ERROR :: island node, reason : cannot create an island without set a name" << endl;
        return false;
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "image")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "image")){
                    if (this->texture) SDL_DestroyTexture(this->texture);

                    this->texture = loadTexture(attr.value, &this->rect);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: island node, reason : cannot reconize '" << attr.key << "' image attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: island node, reason : cannot reconize '" << child->tag << "' island children" << endl;
        }
    }

    return true;
}

Island::Island(){
    if (IS_LOG_OPEN) LOG << "Island::Island()" << endl;
    this->type = nullptr;
}

Island::~Island(){
    this->type = nullptr;
}

bool Island::load_from_xml(XMLNode* node){

    /*
    <summon-island type="*type name*" angle="*angle*">

    </summon-island/>
    */

    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Island::load_from_xml, reason : cannot load it from a null xml node" << endl;
        return false;
    }
    Island* island = new Island();
    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "type")){
            island->set(attr.value);
        } else if (!strcmp(attr.key, "angle")){
            int angle;
            sscanf(attr.value, "%d", &angle);
            island->setAngle(angle);
        }
    }
}

Island_type_list::Island_type_list(){
    
}

Island_type_list::~Island_type_list(){
    for (Island_type* type : this->types){
        if (type) delete type;
    }
    this->types.clear();
}

Island_type* Island_type_list::search(string name){
    for (Island_type* type : this->types){
        if (type == name){
            return type;
        }
    }
    return nullptr;
}

Island_type_list& operator<<(Island_type_list& list, Island_type* type){
    list.push(type);
    return list;
}

bool operator==(Island_type* type, string name){
    if (type->getName() == name) return true;
    return false;
}

bool Island::set(string name){

}

Island_list& operator<<(Island_list& list, Island* type){
    list.push(type);
    return list;
}