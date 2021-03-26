#include <cstdlib>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "ui/graphics/particles.hpp"
#include "ui/graphics/light.hpp"
#include "main.hpp"

Particles::Particles(){
    unlink();
}

Particles::~Particles(){
    unlink();
}

void Particles::unlink(void){
    type = nullptr;

    for (Particle* p : particles){
        if (p){
            if (p->light) delete p->light;
            delete p;
        }
        p = nullptr;
    }

    particles.clear();
    pos.x = 0;
    pos.y = 0;
}

bool Particles::set(string type_name){
    type = searchParticle(type_name);
    pushing = true;
    return type;
}

void Particles::pushParticle(void){
    if (!type) return;

    Particle *p = new Particle;
    p->tick = SDL_GetTicks();
    p->vector.x = cosf(getRandAngle() * (M_PI / 180.0f)) * type->getStrength();
    p->vector.y = sinf(getRandAngle() * (M_PI / 180.0f)) * type->getStrength();

    p->pos.x = pos.x;
    p->pos.y = pos.y;

    p->r = getR();
    p->g = getG();
    p->b = getB();
    p->a = getA();

    p->light = nullptr;

    /*
    if (!type->getLight().empty()){
        p->light = new Light();

        if (p->light->set(type->getLight())){
            p->light->setPos(p->pos.x, pos.y);
            p->light->setZ(z);

            LIGHTS.push_back(p->light);
        } else {
            delete p->light;
            p->light = NULL;
        }
    }
    */

    particles.push_back(p);
}

void Particles::setPos(int x, int y){
    pos.x = x;
    pos.y = y;
}

int Particles::getZ(void){
    return z;
}

void Particles::setZ(int z){
    this->z = z;
}

bool Particles::drawLight(int z){
    if (!type) return false;

    return true;
}

bool Particles::draw(int z){
    if (!type) return false;
    if (this->z != z) return true;

    int tick = SDL_GetTicks();
    int i = 0;

    for (Particle* p : particles){
        switch (type->getStyle()){
            
            case Particles_type::Particle_circle:
                if (type->getStyleType()->circle.filled){
                    if (filledCircleRGBA(RENDERER, p->pos.x + CAMERA.x, p->pos.y + CAMERA.y, type->getStyleType()->circle.radius, p->r, p->g, p->b, p->a)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: filledCircleRGBA, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                } else {
                    if (circleRGBA(RENDERER, p->pos.x + CAMERA.x, p->pos.y + CAMERA.y, type->getStyleType()->circle.radius, p->r, p->g, p->b, p->a)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: circleRGBA, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                }
                break;
            
            case Particles_type::Particle_ellipse:
                if (type->getStyleType()->ellipse.filled){
                    if (filledEllipseRGBA(RENDERER, p->pos.x + CAMERA.x, p->pos.y + CAMERA.y, type->getStyleType()->ellipse.Vradius, type->getStyleType()->ellipse.Hradius, p->r, p->g, p->b, p->a)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: filledEllipseRGBA, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                } else {
                    if (ellipseRGBA(RENDERER, p->pos.x + CAMERA.x, p->pos.y + CAMERA.y, type->getStyleType()->ellipse.Vradius, type->getStyleType()->ellipse.Hradius, p->r, p->g, p->b, p->a)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: ellipseRGBA, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                }
                break;
            
            case Particles_type::Particle_point:
                SDL_SetRenderDrawColor(RENDERER, p->r, p->g, p->b, p->a);
                if (SDL_RenderDrawPoint(RENDERER, p->pos.x + CAMERA.x, p->pos.y + CAMERA.y)){
                    if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawPoint, reason : " << SDL_GetError() << endl;
                    return false;
                }
                break;
            
            case Particles_type::Particle_square:
                SDL_Rect rect;
                
                rect.x = p->pos.x - (type->getStyleType()->square.width / 2) + CAMERA.x;
                rect.y = p->pos.y - (type->getStyleType()->square.width / 2) + CAMERA.y;
                rect.w = type->getStyleType()->square.width;
                rect.h = type->getStyleType()->square.width;

                if (type->getStyleType()->square.filled){
                    if (SDL_RenderDrawRect(RENDERER, &rect)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawRect, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                } else {
                    if (SDL_RenderFillRect(RENDERER, &rect)){
                        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawRect, reason : " << SDL_GetError() << endl;
                        return false;
                    }
                }
                break;
            
            default:
                break;
        }
    }
    return true;
}

int Particles::getRandAngle(void){
    return (rand() % range) + (angle - range/2);
}

int Particles::getR(void){
    int def = max(type->getEndColor().r, type->getStartColor().r) - min(type->getEndColor().r, type->getStartColor().r);
    if (abs(def)) return rand() % def + min(type->getEndColor().r, type->getStartColor().r);
    return 0;
}

int Particles::getG(void){
    int def = max(type->getEndColor().g, type->getStartColor().g) - min(type->getEndColor().g, type->getStartColor().g);
    if (abs(def)) return rand() % def + min(type->getEndColor().g, type->getStartColor().g);
    return 0;
}

int Particles::getB(void){
    int def = max(type->getEndColor().b, type->getStartColor().b) - min(type->getEndColor().b, type->getStartColor().b);
    if (abs(def)) return rand() % def + min(type->getEndColor().b, type->getStartColor().b);
    return 0;
}

int Particles::getA(void){
    int def = max(type->getEndColor().a, type->getStartColor().a) - min(type->getEndColor().a, type->getStartColor().a);
    if (abs(def)) return rand() % def + min(type->getEndColor().a, type->getStartColor().a);
    return 0;
}

void Particles::setRange(int range){
    this->range = range;
}

void Particles::setAngle(int angle){
    this->angle = angle;
}

void Particles::setDuration(int duration){
    if (duration != UNDEFINE) tick = SDL_GetTicks() + duration;
    else tick = UNDEFINE;
}

bool Particles::should_delete(void){
    if (tick != UNDEFINE) return (SDL_GetTicks() >= tick);
    return false;
}

void Particles::pushParticles(void){
    if (pushing){
        for (int i=0; i<type->getDensity(); i++){
            pushParticle();
        }
    }
}

void Particles::push(bool push){
    pushing = push;
}

void Particles::update(void){
    int i=0;
    for (Particle* p : particles){
        if (p){
            if (tick - p->tick >= type->getTime()){
                particles.erase(particles.begin() + i);

                //if (p->light) delete p->light;
                p->light = nullptr;
                delete p;
                continue;
            }
        
            p->pos.x += p->vector.x * DELTA_TIME;
            p->pos.y += p->vector.y * DELTA_TIME;

            if (p->light){
                p->light->setPos(p->pos.x + CAMERA.x, p->pos.y + CAMERA.y);
            }

        } else {
            particles.erase(particles.begin() + i);
            delete p;
            continue;
        }

        i++;
    }
    
    pushParticles();
}

Particles_type* Particles::getType(void){
    return type;
}

Particles* operator<<(Particles* p, string name){
    if (!p) return nullptr;
    p->set(name);
    return p;
}

bool operator==(Particles* p, string name){
    return p->getType()->getName() == name;
}

int update_particles(void* ptr){
    
    int i=0;
    for (Particles* p : PARTICLES){
        if (p->should_delete()){
            delete p;
            p = nullptr;
            PARTICLES.erase(PARTICLES.begin() + i);
            continue;
        }

        p->update();
        i++;
    }
    
    return 1;
}

void draw_particles(int z){
    for (Particles* p : PARTICLES){
        p->draw(z);
    }
}

void clear_particles(void){
    for (Particles* p : PARTICLES){
        delete p;
    }
    PARTICLES.clear();
}