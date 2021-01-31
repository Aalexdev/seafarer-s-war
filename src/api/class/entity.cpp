#include "api/class/entity.hpp"
#include "main.hpp"

BoatPart::BoatPart(){
    if (IS_LOG_OPEN) LOG << "BoatPart::BoatPart()" << endl;
    this->name = "part";
}
BoatPart::~BoatPart(){
    if (IS_LOG_OPEN) LOG << "BoatPart::~BoatPart()" << endl;
    this->name.clear();
}

Entity_type::Entity_type(){
    if (IS_LOG_OPEN) LOG << "Entity_type::Entity_type()" << endl;
    this->name = "Uncknow";
    this->rect = (SDL_Rect){0, 0, 0, 0};
}

Entity_type::~Entity_type(){
    if (IS_LOG_OPEN) LOG << "Entity_type::~Entity_type()" << endl;
    if (this->texture) SDL_DestroyTexture(this->texture);
    this->name.clear();

    for (Hitbox* part : this->parts){
        delete part;
    }
    this->parts.clear();
}

bool Entity_type::load_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Entity_type::load_from_xml" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity_load::load_from_xml, reason : cannot load from a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){

            if (!this->used_name(attr.value)){
                this->name = attr.value;
            } else {
                if (IS_ERR_OPEN) ERR << "ERROR :: Entity_type::load_from_xml, reason : name '" << attr.value << "' is erealy used" << endl;
                return false;
            }

            
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' entity attribute" << endl;
        }
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "texture")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "path")){
                    int w=this->rect.w, h=this->rect.h;
                    this->texture = loadTexture(attr.value, &this->rect);
                } else if (!strcmp(attr.key, "w")){
                    sscanf(attr.value, "%d", &this->rect.w);
                } else if (!strcmp(attr.key, "h")){
                    sscanf(attr.value, "%d", &this->rect.h);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' texture attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "perform")){
            for (int c=0; c<child->children.size; c++){
                XMLNode* perform = XMLNode_child(child, c);

                if (!strcmp(perform->tag, "acceleration")){
                    for (int a=0; a<perform->attributes.size; a++){
                        XMLAttribute attr = perform->attributes.data[a];

                        if (!strcmp(attr.key, "max")){
                            sscanf(attr.value, "%d", &this->maxSpeed);
                        } else if (!strcmp(attr.key, "pxPerSec")){
                            int pxPS;
                            sscanf(attr.value, "%d", &pxPS);
                            this->speedDelay = 1000 / pxPS;
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' acceleration attribute" << endl;
                        }
                    }
                } else if (!strcmp(perform->tag, "turnSpeed")){
                    for (int a=0; a<perform->attributes.size; a++){
                        XMLAttribute attr = perform->attributes.data[a];

                        if (!strcmp(attr.key, "max")){
                            sscanf(attr.value, "%d", &this->maxSpeed);
                        } else if (!strcmp(attr.key, "anglePerSec")){
                            int aPS;
                            sscanf(attr.value, "%d", &aPS);
                            this->speedDelay = 1000 / aPS;
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' acceleration attribute" << endl;
                        }
                    }
                }
            }
        } else if (!strcmp(child->tag, "parts")){
            for (int p=0; p<child->children.size; p++){
                XMLNode* partN = XMLNode_child(child, p);

                if (!strcmp(partN->tag, "part")){
                    BoatPart* part = new BoatPart();

                    for (int a=0; a<partN->attributes.size; a++){
                        XMLAttribute attr = partN->attributes.data[a];

                        if (!strcmp(attr.key, "name")){
                            part->name = attr.value;
                        } else if (!strcmp(attr.key, "health")){
                            sscanf(attr.value, "%d", &part->health);
                        } else {
                            if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' parts attribute" << endl;
                        }
                    }
                    
                    if (part->read_from_xml(partN)){
                        this->parts.push_back(part);
                    } else {
                        delete part;
                    }
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << partN->tag << "' parts child" << endl;
                }
            }
        } else if (!strcmp(child->tag, "layer")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "max")){
                    sscanf(attr.value, "%d", &this->layerMax);
                } else if (!strcmp(attr.key, "min")){
                    sscanf(attr.value, "%d", &this->layerMin);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << attr.key << "' layer attribute" << endl;
                }
            }
        } else {
            if (IS_LOG_OPEN) ERR << "WARNING :: Entity_type::load_from_xml, reason : cannot reconize '" << child->tag << "' entity child" << endl;
        }
    }

    return true;
}

bool Entity::set(std::string name){
    if (IS_LOG_OPEN) LOG << "Entity::set('" << name << "')" << endl;
    if (name.empty()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::set, reason : cannot load a null type name" << endl;
        return false;
    }

    for (Entity_type* type : ENTITY_TYPES){
        if (type->get_name() == name){
            this->type = type;

            this->rect.w = type->getRect().w;
            this->rect.h = type->getRect().h;

            return true;
        }
    }

    if (IS_ERR_OPEN) ERR << "ERROR :: Entity::set, reason : cannot load '" << name << "' entity name" << endl;
    return false;
}

bool Entity_type::used_name(std::string name){
    for (Entity_type* type : ENTITY_TYPES){
        if (type->get_name() == name){
            return true;
        }
    }
    return false;
}

bool Entity::load_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Entity::load_from_xml()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::load_from_xml, reason : cannot load from a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "x")){
            sscanf(attr.value, "%d", &this->rect.x);
        } else if (!strcmp(attr.key, "y")){
            sscanf(attr.value, "%d", &this->rect.y);
        } else if (!strcmp(attr.key, "type")){
            if (!this->set(attr.value)) return false;
        } else if (!strcmp(attr.key, "height")){
            sscanf(attr.value, "%d", &this->z);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << attr.key  << "' summonEntity attribute" << endl;
        }
    }


    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "team")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "team")){
                    
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << attr.key << "' team attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Entity::load_from_xml, reason : cannot reconize '" << child->tag << "' summonEntity child" << endl;
        }
    }

    return true;
}

Entity::Entity(){
    if (IS_LOG_OPEN) LOG << "Entity::Entity()" << endl;
    this->type = nullptr;
    this->z = 0;
    this->angle = 0;
    this->is_player = false;

    this->speedTicks=0;
    this->turnTicks=0;
    this->speed=0;
}

Entity::Entity(bool isPlayer){
    if (IS_LOG_OPEN) LOG << "Entity::Entity()" << endl;
    this->type = nullptr;
    this->z = 0;
    this->angle = 0;
    this->is_player = isPlayer;

    this->speedTicks=0;
    this->turnTicks=0;
    this->speed=0;
}
Entity::~Entity(){
    if (IS_LOG_OPEN) LOG << "Entity::~Entity()" << endl;
    
    this->unlink();
}

void Entity::update(){
    while (this->angle >= 360){
        this->angle -= 360;
    }

    if (this->is_player){
        if (KEYPAD->getKey(SDL_SCANCODE_UP)){
            if (this->speed < this->type->getMaxSpeed()) this->speed ++;
        }

        if (KEYPAD->getKey(SDL_SCANCODE_DOWN)){
            if (this->speed > -this->type->getMaxSpeed())this->speed --;
        }

        if (KEYPAD->getKey(SDL_SCANCODE_LEFT)){
            this->angle --;
        }

        if (KEYPAD->getKey(SDL_SCANCODE_RIGHT)){
            this->angle ++;
        }

        cout << "x : " << this->rect.x << ", y : " << this->rect.y << endl;
    }

    if (this->speed!=0){
        int x, y;
        setAngleM(&x, &y, this->speed, this->angle-90);
        this->rect.x += x;
        this->rect.y += y;
    }
}

bool Entity::draw(){
    if (!this->type){
        if (IS_ERR_OPEN) ERR << "ERROR :: Entity::draw, reason : cannot draw a entity who is not linked to a type" << endl;
        return false;
    }

    SDL_Rect temp = {this->rect.x - CAMERA.x, this->rect.y - CAMERA.y, this->rect.w, this->rect.h};
    if (SDL_RenderCopyEx(RENDERER, this->type->getTexture(), NULL, &temp, this->angle, 0, SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopy, reason : " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void Entity::unlink(void){
    this->type = nullptr;

    for (BoatPart* part : this->parts){
        delete part;
    }
    this->parts.clear();
}