#include "api/class/Ammunition.hpp"
#include "main.hpp"

#include <cmath>
#include <math.h>

Ammunition::Ammunition(){
    _type = nullptr;
    _dist = 0;
    _speed = 0;
    _pop = false;
}

Ammunition::~Ammunition(){
    _type = nullptr;
}

bool Ammunition::set(string name){
    _type = search_Ammunition_type(name);
    if (!_type && IS_ERR_OPEN) ERR << "ERROR :: cannot reconize '" << name << "' ammunition type name" << endl;
    else get_type_attributes();
    return _type;
}

bool Ammunition::set(int id){
    _type = search_Ammunition_type(id);
    return _type;
}

void Ammunition::set(Ammunition_type* type){
    _type = type;
}

bool Ammunition::linked(void){
    return _type;
}

float Ammunition::speed(void){
    return _speed;
}

void Ammunition::speed(float speed){
    _speed = speed;
}

void Ammunition::update_speed(void){
    if (_mass && _strength){
        _speed = _strength / _mass;
    } else {
        _speed = 0;
    }
}

void Ammunition::update_pos(void){
    _rect.x += cosf(_angle*M_PI/180.0f) * (_speed * DELTA_TIME);
    _rect.y += sinf(_angle*M_PI/180.0f) * (_speed * DELTA_TIME);
    _dist += _speed * DELTA_TIME;
}

void Ammunition::update_collisions(void){

}

int Ammunition::angle(void){
    return _angle;
}

void Ammunition::angle(int angle){
    _angle = angle;
}

Ammunition_type* Ammunition::type(void){
    return _type;
}

void Ammunition::get_type_attributes(void){
    if (!linked()) return;

    _rect = _type->size();
    _layer_target = _type->target_layer();
    _up_down_speed = _type->up_down_speed();
    _strength = _type->strength();
    _mass = _type->mass();
}

SDL_Rect Ammunition::rect(void){
    return _rect;
}

SDL_Rect* Ammunition::rect_ptr(void){
    return &_rect;
}

float Ammunition::dist(void){
    return _dist;
}

void Ammunition::dist(float dist){
    _dist = dist;
}

float Ammunition::strength(void){
    return _strength;
}

void Ammunition::strength(float strength){
    _strength = strength;
}

float Ammunition::mass(void){
    return _mass;
}

void Ammunition::mass(float mass){
    _mass = mass;
}

bool Ammunition::should_delete(void){
    if (!_type) return true;
    if (_pop) return true;

    if (_type->layer_target_type() == AMMUNITION_TYPE_TARGET_NONE) return false;
    if (_type->layer_target_type() == AMMUNITION_TYPE_TARGET_EQUAL) return floor(_z) == _type->target_layer();
    if (_type->layer_target_type() == AMMUNITION_TYPE_TARGET_LESS) return _z < _type->target_layer();
    if (_type->layer_target_type() == AMMUNITION_TYPE_TARGET_GREATER) return _z > _type->target_layer();

    return _dist >= AMMUNITION_MAX_DIST;
}

int Ammunition::x(void){
    return _rect.x + (_rect.w / 2) + CAMERA.x; 
}

int Ammunition::y(void){
    return _rect.y + (_rect.h / 2) + CAMERA.y; 
}

float Ammunition::z(void){
    return _z;
}

void Ammunition::pop(void){
    _pop = true;
}

bool Ammunition::draw(void){
    if (!_type) return false;

    if (SDL_RenderCopyEx(RENDERER, _type->texture(), NULL, rect_ptr(), _angle+90, _type->center_ptr(), SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopyEx, reason : " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void Ammunition::x(int x){
    _rect.x = x;
}

void Ammunition::y(int y){
    _rect.y = y;
}

void Ammunition::z(float z){
    _z = z;
}

Ammunition* push_Ammunition(string name){
    Ammunition* amm = new Ammunition();

    if (amm->set(name)){
        AMMUNITIONS.push_back(amm);
    } else {
        delete amm;
        amm = nullptr;
    }

    return amm;
}

int update_ammunitions(void* ptr){
    int i=0;
    for (Ammunition* amm : AMMUNITIONS){
        if (amm->should_delete()){
            delete amm;
            amm = nullptr;
            AMMUNITIONS.erase(AMMUNITIONS.begin() + i);
            continue;
        }

        amm->update_speed();
        amm->update_pos();
        amm->update_collisions();

        i++;
    }

    return 1;
}

int draw_ammunitions(int z){

    int i=0;
    for (Ammunition* amm : AMMUNITIONS){
        if ((int)amm->z() == z){
            if (!amm->draw()){
                delete amm;
                amm = nullptr;
                AMMUNITIONS.erase(AMMUNITIONS.begin() + i);
                continue;
            }
        }
        i++;
    }
    return 1;
}

void clear_ammunitions(void){
    for (Ammunition* amm : AMMUNITIONS){
        delete amm;
    }
    AMMUNITIONS.clear();
}

Ammunition* operator<<(Ammunition& amm, string type_name){
    amm.set(type_name);
    return &amm;
}

Ammunition* operator<<(Ammunition& amm, int type_id){
    amm.set(type_id);
    return &amm;
}

Ammunition* operator<<(Ammunition& amm, Ammunition_type* type){
    amm.set(type);
    return &amm;
}

bool operator==(Ammunition& amm, Ammunition_type* type){
    if (amm.linked()){
        return amm.type() == type;
    }
    return false;
}

bool operator==(Ammunition& amm, string type_name){
    if (amm.linked()){
        return amm.type()->name() == type_name;
    }
    return false;
}

bool operator==(Ammunition& amm, int type_id){
    if (amm.linked()){
        return amm.type()->id() == type_id;
    }
    return false;
}