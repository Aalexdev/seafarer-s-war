#include "ui/graphics/light.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include "main.hpp"

void light(int power, int x, int y, int r, int g, int b){
    for (int i=0; i<power; i+=5){
        if (i > power / 3){
            filledCircleRGBA(RENDERER, x, y, i, r, g, b, 10);
        }
    }
}

void projectedLight(int angle, int range, int x, int y, int r, int g, int b, int a, int radius){
    
    for (int i=0; i<range/2; i++){
        int rx, ry;
        setAngleM(&rx, &ry, radius, i+angle+(range/2));
        int lx, ly;
        setAngleM(&lx, &ly, radius, i+angle-(range));
        
        filledTrigonRGBA(RENDERER, x, y, rx+x, ry+y, lx+x, ly+y, r, g, b, a);
    }   
}

Light_type::Light_type(){
    if (IS_LOG_OPEN) LOG << "Light_type::Light_type()" << endl;
    texture = NULL;
}

Light_type::~Light_type(){
    if (IS_LOG_OPEN) LOG << "~Light_type::Light_type()" << endl;
    if (texture) SDL_DestroyTexture(texture);
}

bool Light_type::load(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Light_type::load()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Light_type::load, reason : cannot load a light type from a null xml node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            name = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: light, reason : cannot reconize '" << attr.value << " light attribute" << endl;
        }
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "texture")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "path")){
                    texture = loadTexture(attr.value, &size);
                } else if (!strcmp(attr.key, "w")){
                    sscanf(attr.value, "%d", &size.w);
                } else if (!strcmp(attr.key, "h")){
                    sscanf(attr.value, "%d", &size.h);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: light, texture, reason : cannot reconize '" << attr.key << "' texture attribute" << endl;
                }
            }

            center.x = size.w / 2;
            center.y = size.h / 2;

        } else if (!strcmp(child->tag, "center")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "x")){
                    sscanf(attr.value, "%d", &center.x);
                } else if (!strcmp(attr.key, "y")){
                    sscanf(attr.value, "%d", &center.y);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: light, center, reason : cannot reconize '" << attr.key << "' center attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: light, reason : cannot reconize '" << child->tag << "' light attribute" << endl;
        }
    }

    return true;
}

string Light_type::getName(void){
    return name;
}

SDL_Rect Light_type::getSize(void){
    return size;
}

SDL_Texture* Light_type::getTexture(void){
    return texture;
}

SDL_Point* Light_type::getCenter(void){
    return &center;
}

Light::Light(){
    type = nullptr;
    angle = 0;
}

Light::~Light(){
    type = nullptr;
}

bool Light::set(string name){
    type = searchLight(name);
    if (!type) return false;

    resetSize();
    return true;
}

bool Light::draw(int z){
    if (!type) return false;
    if (z != this->z) return true;

    SDL_Rect rect = {this->rect.x - type->getCenter()->x, this->rect.y - type->getCenter()->y, this->rect.w, this->rect.h};
    if (SDL_RenderCopyEx(RENDERER, type->getTexture(), NULL, &rect, angle, type->getCenter(), SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopyEX, reason : " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

void Light::setPos(int x, int y){
    rect.x = x;
    rect.y = y;
}

void Light::setSize(int w, int h){
    rect.w = w;
    rect.h = h;
}

void Light::resetSize(void){
    if (!type) return;

    rect.w = type->getSize().w;
    rect.h = type->getSize().h;
}

void Light::setAngle(int angle){
    this->angle = angle;
}

void Light::setZ(int z){
    this->z = z;
}

Light_type* searchLight(string name){
    for (Light_type* t : LIGHT_TYPES){
        if (t->getName() == name){
            return t;
        }
    }
    return nullptr;
}

void pushLight_type(XMLNode* node){
    Light_type* type = new Light_type();

    if (type->load(node)){
        LIGHT_TYPES.push_back(type);
    } else {
        delete type;
    }
}

void clearLights(void){
    for (Light_type* type : LIGHT_TYPES){
        delete type;
    }
    LIGHT_TYPES.clear();
}

Light* newLight(void){
    return new Light();
}