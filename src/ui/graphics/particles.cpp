#include <cstdlib>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "ui/graphics/particles.hpp"
#include "ui/graphics/light.hpp"
#include "main.hpp"

Particles::Particles(){
    _type = nullptr;
    _pushing = true;
    _del = false;
    _ticks = SDL_GetTicks();
    _duration = 0;
    _particles_duration = 500;
}

Particles::~Particles(){
    if (IS_LOG_OPEN) LOG << "Particles::~Particles()" << endl;
    _type = nullptr;
}

Particles_type* Particles::type(void){
    return _type;
}

void Particles::type(Particles_type* type){
    _type = type;
}

bool Particles::type(string type_name){
    _type = search_particle_type(type_name);
    return _type;
}

vector<Particle*> Particles::particles(void){
    return _particles;
}

void Particles::push(void){
    Particle* p = create_Particle();

    p->angle(_angle);
    p->range(_range);
    p->pos(_pos);
    p->create_random_vectorf(1);
    p->duration(500);
    p->color(_type->get_random_color());

    _particles.push_back(p);
}

float Particles::radius(void){
    return _radius;
}

void Particles::radius(float radius){
    _radius = radius;
}

int Particles::angle(void){
    return _angle;
}

void Particles::angle(int angle){
    _angle = angle;
}

int Particles::range(void){
    return _range;
}

void Particles::range(int range){
    _range = range;
}

SDL_Point Particles::pos(void){
    return _pos;
}

void Particles::pos(SDL_Point pos){
    _pos = pos;
}

float Particles::density(void){
    return _density;
}

void Particles::density(float density){
    _density = density;
}

void Particles::update(void){
    int i=0;
    for (Particle* p : _particles){
        if (p->del()){
            delete p;
            _particles.erase(_particles.begin() + i);
            p = nullptr;
            continue;
        }
        p->update();

        i++;
    }


    if (_pushing){
        for (int i=0; i<(_density * (float)DELTA_TIME); i++){
            push();
        }
    }

    if (_duration == PARTICLES_DUARTION_EMPTY){
        _del = _particles.empty();
    } else if (_duration != PARTICLES_DURATION_UNLIMITED){
        _del = (SDL_GetTicks() - _ticks > _duration);
    }
}

bool Particles::draw(int z){
    if (_z == z){
        for (Particle* p : _particles){
            if (!p->draw()) return false;
        }
    }
    return true;
}

int Particles::z(void){
    return _z;
}

void Particles::z(int z){
    _z = z;
}

void Particles::pushing(bool pushing){
    _pushing = pushing;
}

bool Particles::del(void){
    return _del;
}

int Particles::duration(void){
    return _duration;
}

void Particles::duration(int duration){
    _duration = duration;
}

int Particles::particles_duration(void){
    return _particles_duration;
}

void Particles::particles_duration(int duration){
    _particles_duration = duration;
}

// ------------------------------

Particles* create_particle(void){
    if (IS_LOG_OPEN) LOG << "create_particle()" << endl;
    Particles* p = new Particles();
    PARTICLES.push_back(p);
    return p;
}

int update_particles(void* ptr){
    int i=0;
    for (Particles* p : PARTICLES){
        if (p->del()){
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
        if (!p->draw(z)){
            MAINVAR->launched = false;
            break;
        }
    }
}

void clear_particles(void){
    for (Particles* p : PARTICLES){
        delete p;
    }
    PARTICLES.clear();
}
