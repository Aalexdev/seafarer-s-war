#include "api/class/equipment.hpp"
#include "main.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"

Equipment_type::Equipment_type(){
    if (IS_LOG_OPEN) LOG << "Equipment_type::Equipment_type()" << endl;

    texture = nullptr;
    light = nullptr;
    cannon = nullptr;

    rect = {0, 0, 0, 0};
}

Equipment_type::~Equipment_type(){
    if (IS_LOG_OPEN) LOG << "Equipment_type::~Equipment_type()" << endl;

    freeTexture();
    if (light) delete light;
    if (cannon) delete cannon;
}

bool Equipment_type::loadXML(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Equipment_type::loadXML()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Equipment_type::loadXML, reason : cannot load an quipment type from a NULL xml Node" << endl;
        return false;
    }

    /*
    key* : obtionnal

    <equipment name="name">
        <texture path="" w*="rect.w" h*="rect.h"/>
        <light power="power" max-range="maxRange"/>
        <cannon />
    </equipment> 
    */

   for (int a=0; a<node->attributes.size; a++){
       XMLAttribute attr = node->attributes.data[a];

       if (!strcmp(attr.key, "name")){
           name = attr.value;
       } else {
           if (IS_ERR_OPEN) ERR << "WARNING :: equipment, reason : cannot reconize '" << attr.key << " attribute" << endl;
       }
   }

   if (name.empty()){
       if (IS_ERR_OPEN) ERR << "ERROR :: equipment, reason : cannot create an equipment without a name" << endl;
       return false;
   }

   for (int c=0; c<node->children.size; c++){
       XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "texture")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "path")){
                    texture = loadTexture(attr.value, &rect);
                } else if (!strcmp(attr.key, "w")){
                    sscanf(attr.value, "%d", &rect.w);
                } else if (!strcmp(attr.key, "h")){
                    sscanf(attr.value, "%d", &rect.h);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: equipment; texture, reason : cannot reconize '" << attr.key << " texture attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "center")){
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "x")){
                    sscanf(attr.value, "%d", &center.x);
                } else if (!strcmp(attr.key, "y")){
                    sscanf(attr.value, "%d", &center.y);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: equipment; center, reason : cannot reconize '" << attr.key << "' center attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "light")){
            light = new Light;
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "power")){
                    sscanf(attr.value, "%d", &light->power);
                } else if (!strcmp(attr.key, "max-range")){
                    sscanf(attr.value, "%d", &light->maxRange);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: equipment; light, reason : cannot reconize '" << attr.key << " light attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "cannon")){
            cannon = new Cannon;

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (false){

                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: equipment; cannon, reason : cannot reconize '" << attr.key << " cannon attribute" << endl;
                }
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: equipment, reason : cannot reconize '" << child->tag << " equipment children" << endl;
        }
   }

    return true;
}

void Equipment_type::freeTexture(void){
    if (texture) SDL_DestroyTexture(texture);
}

Equipment_type::Cannon* Equipment_type::getCannon(){
    return cannon;
}

Equipment_type::Light* Equipment_type::getLight(){
    return light;
}

SDL_Point* Equipment_type::getCenter(void){
    return &center;
}

SDL_Texture* Equipment_type::getTexture(void){
    return texture;
}

SDL_Rect Equipment_type::getRect(){
    return rect;
}

string Equipment_type::getName(){
    return name;
}

Equipment_type* search(string name){
    for (Equipment_type* e : EQUIPMENTS){
        if (name == e->getName()){
            return e;
        }
    }

    if (IS_ERR_OPEN) ERR << "ERROR :: canot found '" << name << "' equipment name" << endl;
    return NULL;
}

Equipment::Equipment(){

}

Equipment::~Equipment(){
    unlink();
}

bool Equipment::drawLight(void){
    if (!type->getLight()) return true;
    if (light){
    
        if (light->range == 0) light->range = 1;

        
        if (filledPieRGBA(RENDERER, type->getCenter()->x + rect.x, type->getCenter()->y + rect.y, type->getLight()->power, angle - (light->range / 2) - 90, angle + (light->range / 2) - 90, 255, 255, 255, 100)){
            if (IS_ERR_OPEN) ERR << "ERROR :: filledPieRGBA, reason : " << SDL_GetError() << endl;
            return false;
        }
    
    }

    return true;
}

bool Equipment::draw(void){

    if (angleTarget > angle){
        angle++;
    } else if (angleTarget < angle){
        angle--;
    }

    if (SDL_RenderCopyEx(RENDERER, type->getTexture(), NULL, &rect, angle, type->getCenter(), SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopyEx, reason : " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

bool Equipment::setType(string name){
    unlink();
    type = search(name);

    if (type){
        rect = type->getRect();
    }

    if (type->getLight()){
        light = new Light;
    }
    
    return type;
}

void Equipment::unlink(void){
    this->rect = {0, 0, 0, 0};
    if (light) delete light;
    if (cannon) delete cannon;
    type = nullptr;
}

void Equipment::setAngle(int angle){
    this->angle = angle;
}

void Equipment::setAngleTarget(int angle){
    this->angleTarget = angle;
}

void Equipment::setPos(int x, int y){
    rect.x = x - type->getCenter()->x;
    rect.y = y - type->getCenter()->y;
}

void Equipment::setTarget(int x, int y){
    angleTarget = -getAngleM(rect.x + type->getCenter()->x, rect.y + type->getCenter()->y, x, y);
}