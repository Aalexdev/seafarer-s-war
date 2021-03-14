#include "ui/graphics/animation.hpp"

Animation::Animation(){
    duration = 1000;
}

void Animation::setDuration(int duration){
    this->duration = duration;
}

int* Animation::Duration(void){
    return &duration;
}