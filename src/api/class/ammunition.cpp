#include "api/class/ammunition.hpp"
#include "main.hpp"
#include "ui/graphics/light.hpp"

#include <string.h>

Ammunition_type::Ammunition_type(){
    if (IS_LOG_OPEN) LOG << "Ammunition_type::Ammunition_type()" << endl;
    texture = nullptr;
    damages = 0;
    initialSpeed = 10;

    type = "unknown";
    name = "unknown";
}

Ammunition_type::~Ammunition_type(){
    if (IS_LOG_OPEN) LOG << "Ammunition_type::~Ammunition_type()" << endl;
    if (texture) SDL_DestroyTexture(texture);

    name.clear();
    type.clear();
}

bool Ammunition_type::loadFrom_XML(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Ammunition_type::loadFrom_XML()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Ammunition_type::loadFrom_XML, reason : cannot load an ammunition from a null XML node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            name = attr.value;
        } else if (!strcmp(attr.key, "type")){
            type = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: ammunition, reason : cannot reconize '" << attr.key << "' ammunition attribute" << endl;
        }
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode *child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "texture")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "texture")){
                    texture = loadTexture(attr.value, &rect);

                    if (texture) SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MUL);
                } else if (!strcmp(attr.key, "w")){
                    sscanf(attr.value, "%d", &rect.w);
                } else if (!strcmp(attr.key, "h")){
                    sscanf(attr.value, "%d", &rect.h);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNIG :: ammunition; texture, reason : cannot reconize '" << attr.key << "' texture attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "perform")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "damages")){
                    sscanf(attr.value, "%d", &damages);
                } else if (!strcmp(attr.key, "initial-speed")){
                    sscanf(attr.value, "%d", &initialSpeed);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: ammunition; perform, reason :  cannot reconize '" << attr.key << "' perform attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "light")){
            light = new Light;
            if (texture) SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "r")){
                    sscanf(attr.value, "%d", &light->r);
                } else if (!strcmp(attr.key, "g")){
                    sscanf(attr.value, "%d", &light->g);
                } else if (!strcmp(attr.key, "b")){
                    sscanf(attr.value, "%d", &light->b);
                } else if (!strcmp(attr.key, "strength")){
                    sscanf(attr.value, "%d", &light->strength);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: ammunition; light, reason : cannot reconize '" << attr.key << "' light attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: ammunition, reason : cannot reconize '" << child->tag << "' ammunition child" << endl;
        }
    }

    return true;
}

SDL_Texture* Ammunition_type::getTexture(void){
    return texture;
}

string Ammunition_type::getName(void){
    return name;
}

string Ammunition_type::getType(void){
    return type;
}

SDL_Rect Ammunition_type::getSize(void){
    return (SDL_Rect){0, 0, rect.w, rect.h};
}

int Ammunition_type::getInitialSpeed(void){
    return initialSpeed;
}

int Ammunition_type::getDamages(void){
    return damages;
}

Ammunition_type::Light* Ammunition_type::getLight(void){
    return light;
}

Ammunition::Ammunition(Entity* parent) : parent(parent){
    if (IS_LOG_OPEN) LOG << "Ammunition::Ammunition()" << endl;
    unlink();
}

Ammunition::Ammunition(Entity* parent, int angle, int x, int y) : parent(parent){
   if (IS_LOG_OPEN) LOG << "Ammunition::Ammunition()" << endl;
    unlink();
    this->angle = angle;
    rect.x = x;
    rect.y = y;
    spoint.x = x;
    spoint.y = y;
    should_delete = true;
}

Ammunition::~Ammunition(){
    if (IS_LOG_OPEN) LOG << "Ammunition::~Ammunition()" << endl;
    unlink();
}

void Ammunition::unlink(void){
    if (IS_LOG_OPEN) LOG << "Ammunition::unlink()" << endl;
    type = nullptr;
    rect = {0, 0, 0, 0};
    speed = 0;
    angle = 0;
}

bool Ammunition::draw(void){
    if (!linked()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Ammunition::draw, reason : cannot draw an unlinked ammunition" << endl;
        return false;
    }

    if (SDL_RenderCopyEx(RENDERER, type->getTexture(), NULL, &rect, angle, 0, SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopyEx(), reason : " << SDL_GetError() << endl;
        return false;
    }

    return is_delete();
}

bool Ammunition::update(void){
    if (!linked()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Ammunition::update, reason : cannot update an unlinked ammunition" << endl;
        return false;
    }

    int x, y;
    setAngleM(&x, &y, speed, angle-90);
    rect.x += x;
    rect.y += y;

    if (getDistanceM(rect.x, rect.y, spoint.x, spoint.y) > 1000){
        return false;
    }
    
    for (Entity* e : ENTITY){
        if (e != parent && e->in_screen() && e->PointInside(getX(), getY())){
            e->setHealth(type->getDamages());
            should_delete = false;
        }
    }

    if (parent != PLAYER){
        if (PLAYER->PointInside(getX(), getY())){
            PLAYER->setHealth(type->getDamages());
            should_delete = false;
        }
    }

    return is_delete();
}

bool Ammunition::load(string type_name){
    type = find(type_name);

    if (!type) return false;

    rect.w = type->getSize().w; 
    rect.h = type->getSize().h; 
    speed = type->getInitialSpeed();
    return true;
}

bool Ammunition::linked(void){
    return type;
}

Ammunition_type* find(string name){
    
    if (IS_LOG_OPEN) LOG << "find('" << name << "')" << endl;
    for (Ammunition_type* a : AMMUNITION_TYPE){
        if (a->getName() == name){
            if (IS_LOG_OPEN) LOG << "find('" << name << "') : found" << endl;
            return a;
        }
    }

    if (IS_ERR_OPEN) ERR << "ERROR :: cannot find '" << name << "' ammunition name" << endl;
    return NULL;
}

vector<Ammunition_type*> searchType(string type){
    vector<Ammunition_type*> ammunitions;
    
    for (Ammunition_type* a : AMMUNITION_TYPE){
        if (a->getType() == type){
            ammunitions.push_back(a);
        }
    }

    return ammunitions;
}

bool existingType(string type){
    for (Ammunition_type* a : AMMUNITION_TYPE){
        if (a->getName() == type){
            return true;
        }
    }
    return false;
}

void Ammunition::drawLight(void){
    if (!type->getLight()) return;

    light(type->getLight()->strength, rect.x, rect.y, type->getLight()->r, type->getLight()->g, type->getLight()->b);
}

int Ammunition::getX(void){
    return rect.x + (rect.w / 2);
}

int Ammunition::getY(void){
    return rect.y + (rect.h / 2);
}

bool Ammunition::is_delete(void){
    return should_delete;
}