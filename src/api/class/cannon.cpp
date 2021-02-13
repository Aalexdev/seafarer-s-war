#include "api/class/cannon.hpp"
#include "main.hpp"

Cannon_type::Cannon_type(){
    this->sprite = new Sprite();   
}

Cannon_type::~Cannon_type(){
    delete this->sprite;
}

bool Cannon_type::read_from_xml(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Cannon_type::read_from_xml, reason : cannot read a null node" << endl;
        return false;
    }
}

