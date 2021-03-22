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
    light = nullptr;
    cannon = nullptr;

    rect = {0, 0, 0, 0};
}

Equipment_type::~Equipment_type(){
    if (IS_LOG_OPEN) LOG << "Equipment_type::~Equipment_type()" << endl;

    freeTexture();
    if (light){
        if (light->rect) delete light->rect;
        if (light->lightCenter) delete light->lightCenter;
        if (light->ligthTexture) SDL_DestroyTexture(light->ligthTexture);
        delete light;
    }
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
            light = new Light;
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "power")){
                    sscanf(attr.value, "%d", &light->power);
                } else if (!strcmp(attr.key, "range")){
                    sscanf(attr.value, "%d", &light->range);
                } else if (!strcmp(attr.key, "r")){
                    sscanf(attr.value, "%d", &light->r);
                } else if (!strcmp(attr.key, "g")){
                    sscanf(attr.value, "%d", &light->g);
                } else if (!strcmp(attr.key, "b")){
                    sscanf(attr.value, "%d", &light->b);
                } else if (!strcmp(attr.key, "a")){
                    sscanf(attr.value, "%d", &light->a);
                } else if (!strcmp(attr.key, "image")){
                    light->rect = new SDL_Rect;
                    light->lightCenter = new SDL_Point;
                    light->ligthTexture = loadTexture(attr.value, light->rect);

                    if (!light->ligthTexture){
                        delete light->rect;
                        delete light->lightCenter;
                        light->rect = nullptr;
                        light->lightCenter = nullptr;
                    }
                } else if (!strcmp(attr.key, "width")){
                    if (!light->rect) if (IS_ERR_OPEN) ERR << "ERROR :: equipment; light, width, reason : cannot set the width of a the light image without load it, use image=\"path\"" << endl;
                    sscanf(attr.value, "%d", &light->rect->w);
                } else if (!strcmp(attr.key, "height")){
                    if (!light->rect) if (IS_ERR_OPEN) ERR << "ERROR :: equipment; light, height, reason : cannot set the height of a the light image without load it, use image=\"path\"" << endl;
                    sscanf(attr.value, "%d", &light->rect->h);
                } else if (!strcmp(attr.key, "center-x")){
                    if (!light->lightCenter) if (IS_ERR_OPEN) ERR << "ERROR :: equipment; light, height, reason : cannot set the rotationnal center of a the light image without load it, use image=\"path\"" << endl;
                    sscanf(attr.value, "%d", &light->lightCenter->x);
                } else if (!strcmp(attr.key, "center-y")){
                    if (!light->lightCenter) if (IS_ERR_OPEN) ERR << "ERROR :: equipment; light, height, reason : cannot set the rotationnal center of  a the light image without load it, use image=\"path\"" << endl;
                    sscanf(attr.value, "%d", &light->lightCenter->y);
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

                    if (cannon->ammunition_type != UNKNOWN_AMMUNITION){
                        if (!existingType(cannon->ammunition_type)){
                            if (IS_ERR_OPEN) ERR << "WARNING :: equipment; cannon; ammunition-type, reason : cannot reconize '" << attr.value << "' type of ammunition, use unknown to use they all" << endl;
                            cannon->ammunition_type.clear();
                        }
                    }
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

    if (cannon){
        for (Ammunition *a : cannon->ammunitions){
            a->drawLight();
        }
    }

    if (!light) return true;

    projectedLight(angle-90, type->getLight()->range, getX(), getY(), light->r, light->g, light->b, light->a, 1000);

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
    
    if (cannon){
        int i=0;
        for (Ammunition* amm : cannon->ammunitions){
            if (amm){
                if (!amm->draw()) return false;
            } else {
                cannon->ammunitions.erase(cannon->ammunitions.begin() + i);
                i--;
            }
            i++;
        }
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

    if (type->getLight()){
        light = new Light;

        light->r = type->getLight()->r;
        light->g = type->getLight()->g;
        light->b = type->getLight()->b;
        light->a = type->getLight()->a;
    }
    if (type->getCannon()){
        cannon = new Cannon;
        cannon->tick = SDL_GetTicks();
    }
    
    if (IS_LOG_OPEN) LOG << "Equipment::setType() : found '" << name << "'" << endl;
    return type;
}

void Equipment::unlink(void){
    if (IS_LOG_OPEN) LOG << "Equipment::unlink()" << endl;
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
        Ammunition* amm = new Ammunition(parent, angle, getX() - CAMERA.x, getY() - CAMERA.y);

        if (amm->load(type->getCannon()->ammunition_type)){
            cannon->ammunitions.push_back(amm);
        } else {
            delete amm;
        }
    }
}

void Equipment::update(void){
    if (cannon){
        int i=0;
        for (Ammunition* amm : cannon->ammunitions){
            if (amm){
                if (!amm->update()){
                    cannon->ammunitions.erase(cannon->ammunitions.begin() + i);
                    delete amm;
                    i--;
                }
            } else {
                cannon->ammunitions.erase(cannon->ammunitions.begin() + i);
                i--;
            }
            i++;
        }

        if (MOUSEDOWN.left){
            shot();
        }
    }
}