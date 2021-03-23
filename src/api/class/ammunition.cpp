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
    particle_type = NULL;
}

Ammunition_type::~Ammunition_type(){
    if (IS_LOG_OPEN) LOG << "Ammunition_type::~Ammunition_type()" << endl;
    if (texture) SDL_DestroyTexture(texture);

    name.clear();
    type.clear();

    if (particle_type) delete particle_type;
    particle_type = NULL;
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
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "type")){
                    light = attr.value;
                    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: ammunition; light, reason : cannot reconize '" << attr.key << "' light attribute" << endl;
                }
            }
        }  else if (!strcmp(child->tag, "particle")){
            particle_type = new Particle;


            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "type")){
                    particle_type->name = attr.value;
                } else if (!strcmp(attr.key, "angle")){
                    sscanf(attr.value, "%d", &particle_type->angle);
                } else if (!strcmp(attr.key, "range")){
                    sscanf(attr.value, "%d", &particle_type->range);
                } else {
                    if (IS_ERR_OPEN) ERR << "ERROR :: ammunition; particle, reason : cannot reconize '"<< attr.key << "' particle attribute" << endl;
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

string Ammunition_type::getLight(void){
    return light;
}

Ammunition_type::Particle* Ammunition_type::getParticleType(void){
    return particle_type;
}

Ammunition::Ammunition(Entity* parent) : parent(parent){
    unlink();
}

Ammunition::Ammunition(Entity* parent, int angle, int x, int y) : parent(parent){
    light = NULL;
    unlink();
    this->angle = angle;
    rect.x = x;
    rect.y = y;
    spoint.x = x;
    spoint.y = y;
    should_delete = true;
}

Ammunition::~Ammunition(){
    particles->setDuration(3000);
    particles->push(false);
    unlink();
}

void Ammunition::unlink(void){
    type = nullptr;
    rect = {0, 0, 0, 0};
    speed = 0;
    angle = 0;
    particles = NULL;

    if (light) delete light;
    light = NULL;
}

bool Ammunition::draw(void){
    if (!linked()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Ammunition::draw, reason : cannot draw an unlinked ammunition" << endl;
        return false;
    }

    SDL_Rect rect = {getX(), getY(), this->rect.w, this->rect.h};
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

    if (particles){
        particles->setPos(getX(), getY());
        particles->setAngle(angle + type->getParticleType()->angle);
    }

    if (light){
        light->setPos(getX(), getY());
    }

    return is_delete();
}

bool Ammunition::load(string type_name){
    type = find(type_name);
    if (!type) return false;

    rect.w = type->getSize().w; 
    rect.h = type->getSize().h; 
    speed = type->getInitialSpeed();

    if (type->getParticleType()){
        particles = new Particles();

        if (particles->set(type->getParticleType()->name)){
            PARTICLES.push_back(particles);
        
            particles->setAngle(type->getParticleType()->angle);
            particles->setRange(type->getParticleType()->range);
            particles->setDuration(UNDEFINE);

            particles->setZ(parent->getZ());
            particles->setPos(getX(), getY());
        } else {
            delete particles;
            particles = NULL;
        }
    }

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

    return true;
}

bool Ammunition::linked(void){
    return type;
}

Ammunition_type* find(string name){
    
    for (Ammunition_type* a : AMMUNITION_TYPE){
        if (a->getName() == name){
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
    if (type->getLight().empty()) return;

    
}

bool Ammunition::is_delete(void){
    return should_delete;
}

int Ammunition::getX(void){
    return rect.x + (rect.w / 2) + CAMERA.x;
}

int Ammunition::getY(void){
    return rect.y + (rect.h / 2) + CAMERA.y;
}