#include "api/types/Ammunition_type.hpp"
#include "main.hpp"

#ifndef NONE_LAYER_TARGET
    #define NONE_LAYER_TARGET 82638
#endif

Ammunition_type::Ammunition_type(){
    _size = {0, 0, 0, 0};
    _texture = nullptr;
    _center = {0, 0};
    _id = 0;
}

Ammunition_type::~Ammunition_type(){
    if (_texture){
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }

    _name.clear();
}

bool Ammunition_type::load(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Ammunition_type::load(), reason : cannot load an ammunition type with a null xml node" << endl;
        return false;
    }

    /*

    <ammunition name="_name">
        <texture path="_texture" w="_size.w" h="_size.h"/>
        <perform speed="_speed" target-layer="_layer_target" up-down-speed="_up_down_speed"/>
    </ammunition>

    */

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            _name = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: ammunition, reason : cannot reconize '" << attr.key << "' ammunition attribute" << endl;
        }
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "texture")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "path")){
                    _texture = loadTexture(attr.value, size_ptr());
                } else if (!strcmp(attr.key, "w")){
                    sscanf(attr.value, "%d", &_size.w);
                } else if (!strcmp(attr.key, "h")){
                    sscanf(attr.value, "%d", &_size.h);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: ammunition; texture, reason : cannot reconize '" << attr.key << "' texture attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "perform")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "mass")){
                    sscanf(attr.value, "%f", &_mass);
                } else if (!strcmp(attr.key, "strength")){
                    sscanf(attr.value, "%f", &_strength);
                } else if (!strcmp(attr.key, "target-layer")){
                    sscanf(attr.value, "%d", &_layer_target);
                } else if (!strcmp(attr.key, "up-down-speed")){
                    sscanf(attr.value, "%f", &_up_down_speed);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: ammunition; perform, reason : cannot reconize '" << attr.key << "' perform attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "particles")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "type")){
                    _particle_type = attr.value;
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: ammunition, particles, reason : cannot reconize '" << attr.key << "' particles attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: ammunition, reason : cannot reconize '" << child->tag << "' ammunition child" << endl;
        }
    }

    return true;
}

string Ammunition_type::name(void){
    return _name;
}

int Ammunition_type::id(void){
    return _id;
}

SDL_Texture* Ammunition_type::texture(void){
    return _texture;
}

SDL_Rect Ammunition_type::size(void){
    return _size;
}

SDL_Rect* Ammunition_type::size_ptr(void){
    return &_size;
}

float Ammunition_type::strength(void){
    return _strength;
}

SDL_Point Ammunition_type::center(void){
    return _center;
}

SDL_Point* Ammunition_type::center_ptr(void){
    return &_center;
}

int Ammunition_type::target_layer(void){
    return _layer_target;
}

Uint8 Ammunition_type::layer_target_type(void){
    return _layer_target_type;
}

float Ammunition_type::up_down_speed(void){
    return _up_down_speed;
}

float Ammunition_type::mass(void){
    return _mass;
}

void Ammunition_type::mass(float mass){
    _mass = mass;
}

void Ammunition_type::id(int id){
    if (!search_Ammunition_type(id)){
        _id = id;
    }
}

void Ammunition_type::name(string name){
    if (!search_Ammunition_type(name)){
        _name = name;
    }
}

string Ammunition_type::particles_type(void){
    return _particle_type;
}

void Ammunition_type::particules_type(string type){
    _particle_type = type;
}

bool operator<<(Ammunition_type type, XMLNode* node){
    return type.load(node);
}

bool operator==(Ammunition_type type, string name){
    return type.name() == name;
}

bool operator==(Ammunition_type type, int id){
    return type.id() == id;
}

bool new_Ammunition_type(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "new_Ammunition_type" << endl;
    Ammunition_type* type = new Ammunition_type();

    if (type->load(node)){
        AMMUNITION_TYPE.push_back(type);
        return true;
    }

    delete type;
    return false;
}

bool new_Ammunition_type(string file_path){
    return readXML(file_path);
}

Ammunition_type* search_Ammunition_type(string name){
    for (Ammunition_type* t : AMMUNITION_TYPE){
        if (t->name() == name){
            return t;
        }
    }
    return nullptr;
}

Ammunition_type* search_Ammunition_type(int id){
    for (Ammunition_type* t : AMMUNITION_TYPE){
        if (t->id() == id){
            return t;
        }
    }
    return nullptr;
}

void clear_Ammunition_type(void){
    for (Ammunition_type* t : AMMUNITION_TYPE){
        delete t;
        t = nullptr;
    }
    AMMUNITION_TYPE.clear();
}