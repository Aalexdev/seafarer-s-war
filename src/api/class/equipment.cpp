#include "api/class/equipment.hpp"
#include "main.hpp"

#include "SDL2/SDL2_gfxPrimitives.h"
#include "ui/graphics/light.hpp"

#include <cmath>
#include <algorithm>
#include <array>

Equipment_type::Equipment_type(){
    if (IS_LOG_OPEN) LOG << "Equipment_type::Equipment_type()" << endl;

    texture = nullptr;
    light.clear();
    cannon = nullptr;

    rect = {0, 0, 0, 0};
}

Equipment_type::~Equipment_type(){
    if (IS_LOG_OPEN) LOG << "Equipment_type::~Equipment_type()" << endl;

    freeTexture();
    light.clear();
    if (cannon) delete cannon;
}

bool Equipment_type::loadXML(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Equipment_type::loadXML()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Equipment_type::loadXML, reason : cannot load an quipment type from a NULL xml Node" << endl;
        return false;
    }

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
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_MUL);
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
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "type")){
                    light = attr.value;
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: equipment; light, reason : cannot reconize '" << attr.key << " light attribute" << endl;
                }
            }
        } else if (!strcmp(child->tag, "cannon")){
            cannon = new Cannon;

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "couldown")){
                    sscanf(attr.value, "%d", &cannon->couldown);
                } else if (!strcmp(attr.key, "ammunition-type")){
                    cannon->ammunition_type = attr.value;
                } else if (!strcmp(attr.key, "particles")){
                    cannon->particle_type = attr.value;
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

Equipment_type::Cannon* Equipment_type::getCannon(void){
    return cannon;
}

string Equipment_type::getLight(void){
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

Equipment::Equipment(Entity* parent) : parent(parent){
    if (IS_LOG_OPEN) LOG << "Equipment::Equipment()" << endl;
    type = nullptr;
    light = nullptr;
    cannon = nullptr;
    angleMin = -360;
    angleMax = 360;
}

Equipment::~Equipment(){
    if (IS_LOG_OPEN) LOG << "Equipment::~Equipment()" << endl;
    unlink();
}

bool Equipment::drawLight(void){

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
    if (IS_LOG_OPEN) LOG << "Equipment::setType('" << name << "')" << endl;
    if (type)unlink();
    type = search(name);

    if (type){
        rect = type->getRect();
    }

    light = NULL;
    if (!type->getLight().empty()){
        light = new Light();

        if (light->set(type->getLight())){
            light->setPos(getX(), getY());
            light->setZ(parent->getZ());

            LIGHTS.push_back(light);
        } else {
            delete light;
            light = NULL;
        }
    }
    if (type->getCannon()){
        cannon = new Cannon;
        cannon->tick = SDL_GetTicks();
        cannon->particles = nullptr;

        if (!type->getCannon()->particle_type.empty()){
            cannon->particles = new Particles();

            if (cannon->particles->set(type->getCannon()->particle_type)){
                PARTICLES.push_back(cannon->particles);
                cannon->particles->setPos(getX(), getY());
                cannon->particles->push(false);
                cannon->particles->setRange(30);
                cannon->particles->setZ(parent->getZ());
            } else {
                delete cannon->particles;
                cannon->particles = nullptr;
            }
        }
    }
    
    if (IS_LOG_OPEN) LOG << "Equipment::setType() : found '" << name << "'" << endl;
    return type;
}

void Equipment::unlink(void){
    if (IS_LOG_OPEN) LOG << "Equipment::unlink()" << endl;
    rect = {0, 0, 0, 0};

    if (light) delete light;
    light = nullptr;

    if (cannon){
        if (cannon->particles) cannon->particles->setDuration(0);

        for (Ammunition* amm : cannon->ammunitions){
            amm->pop();
        }

        delete cannon;
        cannon = NULL;
    }
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
    target.pos.x = x;
    target.pos.y = y;

    angle = -getAngleM(rect.x + type->getCenter()->x, rect.y + type->getCenter()->y, x, y);

    if (angle > angleMax){
        angle = angleMax;
    } else if (angle < angleMin){
        angle = angleMin;
    }
    
    targetType = Targets::target_pos;
}

void Equipment::setAngleLimit(int min, int max){
    angleMin = min;
    angleMax = max;
}

void Equipment::setTarget(int angle){
    target.speed.rotarySpeed = angle;
    targetType = Targets::target_speed;
}

int Equipment::getX(void){
    return rect.x + type->getCenter()->x;
}

int Equipment::getY(void){
    return rect.y + type->getCenter()->y;
}

void Equipment::shot(void){
    if (!cannon) return;
    if (type->getCannon()->ammunition_type.empty()) return;

    if (SDL_GetTicks() - type->getCannon()->couldown > cannon->tick){
        cannon->tick = SDL_GetTicks();

        Ammunition* amm = push_Ammunition(type->getCannon()->ammunition_type);

        if (amm){
            amm->x(getX());
            amm->y(getY());
            amm->z(parent->getZ());

            amm->angle(angle-90);
            amm->strength(100);

            cannon->ammunitions.push_back(amm);
        }
    }
}

void Equipment::update(void){
    
    if (light){
        light->setPos(getX(), getY());
        light->setAngle(angle);
    }

    if (cannon){
        if (MOUSEBTN.left){
            shot();
        }
    }
}

Equipment_type* Equipment::getType(void){
    return type;
}

int Equipment::getAngle(void){
    return angle;
}