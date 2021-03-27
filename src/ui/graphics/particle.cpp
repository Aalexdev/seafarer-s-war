#include "ui/graphics/particle.hpp"
#include "main.hpp"
#include <cmath>

Particle::Particle(){
    _pos = {0, 0};
    _vector = {0, 0};
    _color = {0, 0, 0, 0};
    _ticks = SDL_GetTicks();
    _duration = 0;
    _del = false;
}

Particle::~Particle(){

}

SDL_Point Particle::pos(void){
    SDL_Point p;
    p.x = _pos.x;
    p.y = _pos.y;
    return p;
}

SDL_FPoint Particle::posf(void){
    return _pos;
}

void Particle::pos(SDL_Point p){
    _pos.x = p.x;
    _pos.y = p.y;
}

void Particle::posf(SDL_FPoint p){
    _pos.x = p.x;
    _pos.y = p.y;
}

SDL_Point Particle::vector(void){
    SDL_Point p;
    p.x = _vector.x;
    p.y = _vector.y;
    return p;
}

SDL_FPoint Particle::vectorf(void){
    return _vector;
}

void Particle::vector(SDL_Point p){
    _vector.x = p.x;
    _vector.y = p.y;
}

void Particle::vectorf(SDL_FPoint p){
    _vector.x = p.x;
    _vector.y = p.y;
}

SDL_Color Particle::color(void){
    return _color;
}

SDL_Color* Particle::color_ptr(void){
    return &_color;
}

void Particle::color(SDL_Color color){
    _color = color;
}

void Particle::create_random_vector(int radius){
    if (!radius) radius = 1;
    _vector.x = cos(random_angle() * M_PI/180) * (rand() % radius);
    _vector.y = sin(random_angle() * M_PI/180) * (rand() % radius);
}

void Particle::create_random_vectorf(int radius){
    if (!radius) radius = 1;
    _vector.x = cosf(random_angle() * M_PI/180) * (rand() % radius+1);
    _vector.y = sinf(random_angle() * M_PI/180) * (rand() % radius+1);
}

void Particle::range(int range){
    _range = range;
}

void Particle::angle(int angle){
    _angle = angle;
}

int Particle::random_angle(void){
    return (rand() % _range) + (_angle - (_range/2));
}

void Particle::update(void){
    _pos.x += _vector.x;
    _pos.y += _vector.y;

    if (SDL_GetTicks() - _ticks > _duration){
        _del = true;
    }
}

bool Particle::draw(void){
    SDL_SetRenderDrawColor(RENDERER, _color.r, _color.g, _color.b, _color.a);
    if (SDL_RenderDrawPoint(RENDERER, _pos.x + CAMERA.x, _pos.y + CAMERA.y)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawPoint, reason : " << SDL_GetError() << endl;
        _del = true;
        return false;
    }
    return true;
}

bool Particle::del(void){
    return _del;
}

int Particle::duration(void){
    return _duration;
}

void Particle::duration(int duration){
    _duration = duration;
}

int Particle::ticks(void){
    return _ticks;
}

void Particle::ticks(int ticks){
    _ticks = ticks;
}

Particle* create_Particle(void){
    return new Particle();
}

void delete_Particle(Particle* p){
    if (p) delete p;
    p = nullptr;
}
