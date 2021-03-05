#include "ui/debug.hpp"

DebugText::DebugText(){
}
DebugText::~DebugText(){
}

bool DebugText::bind(int *value){
    this->value = value;
}

bool DebugText::setPrefix(string prefix){
    this->prefix = prefix;
}

bool DebugText::update(void){
    if ((*this->value) != this->valueBuf){
        cout << this->prefix << this->value << endl;
    }
    return true;
}