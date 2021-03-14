#include "api/event/keypad.hpp"
#include "main.hpp"

Key::Key(){
    this->code = SDL_SCANCODE_0;
}

Key::~Key(){
    this->cmd.clear();
    this->tag.clear();
    this->code = SDL_SCANCODE_0;
}

void Key::setScancode(SDL_Scancode scancode){
    this->code = scancode;
}
void Key::setTag(string tag){
    this->tag = tag;
}
void Key::setCommand(string cmd){
    this->cmd = cmd;
}
SDL_Scancode Key::getScancode(void){
    return this->code;
}
void Key::update(void){
    switch (this->type){
        case Tkey:
            if (KEYPAD->getKey(this->code)) readXML(this->cmd);
            break;
        
        case TkeyUp:
            if (KEYPAD->getKeyUp(this->code)) readXML(this->cmd);
            break;
        
        case TkeyDown:
            if (KEYPAD->getKeyDown(this->code)) readXML(this->cmd);
            break;
        
        default:
            break;
    }
}


bool Key::is_empty(void){
    bool empty = false;

    empty = this->cmd.empty();
    
    return false;
}

void Key::setType(KeyType type){
    this->type = type;
}

Keypad::Keypad(){
    for (int i=0; i<UINT8_MAX; i++){
        this->key[i] = false;
        this->keyDown[i] = false;
        this->keyUp[i] = false;
    }
}

Keypad::~Keypad(){
    for (Key* key : this->keys){
        delete key;
    }
    this->keys.clear();
}

bool Keypad::getKey(SDL_Scancode key){
    return this->key[key];
}
bool Keypad::getKeyUp(SDL_Scancode key){
    return this->keyUp[key];
}
bool Keypad::getKeyDown(SDL_Scancode key){
    return this->keyDown[key];
}

void Keypad::event(SDL_Event e){
    for (int i=0; i<UINT8_MAX; i++){
        this->keyDown[i] = false;
        this->keyUp[i] = false;
    }

    switch(e.type){
        case SDL_KEYDOWN:
            this->keyDown[e.key.keysym.scancode] = true;
            this->key[e.key.keysym.scancode] = true;
            break;
        
        case SDL_KEYUP:
            this->keyUp[e.key.keysym.scancode] = true;
            this->key[e.key.keysym.scancode] = false;
            break;
        
        default:
            break;
    }
}

bool Keypad::read_xml(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Keypad::read_xml, reason : cannot read a null null" << endl;
        return false;
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "key")){
            Key* key = new Key();
            bool push = true;
            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];
                if (!strcmp(attr.key, "tag")){
                    
                    if (!strcmp(attr.key, "UP")){
                        key->setScancode(SDL_SCANCODE_UP);
                    } else if (!strcmp(attr.key, "DOWN")){
                        key->setScancode(SDL_SCANCODE_DOWN);
                    } else if (!strcmp(attr.key, "LEFT")){
                        key->setScancode(SDL_SCANCODE_LEFT);
                    } else if (!strcmp(attr.key, "RIGHT")){
                        key->setScancode(SDL_SCANCODE_RIGHT);
                    } else if (!strcmp(attr.key, "SPACE")){
                        key->setScancode(SDL_SCANCODE_SPACE);
                    } else if (!strcmp(attr.key, "CTR")){
                        key->setScancode(SDL_SCANCODE_LCTRL);
                    } else if (!strcmp(attr.key, "TAB")){
                        key->setScancode(SDL_SCANCODE_TAB);
                    } else if (!strcmp(attr.key, "MAJ lOCK")){
                        key->setScancode(SDL_SCANCODE_CAPSLOCK);
                    } else if (!strcmp(attr.key, "SHIFT LEFT")){
                        key->setScancode(SDL_SCANCODE_LSHIFT);
                    } else if (!strcmp(attr.key, "SHIFT RIGHT")){
                        key->setScancode(SDL_SCANCODE_RSHIFT);
                    } else if (!strcmp(attr.key, "ALT")){
                        key->setScancode(SDL_SCANCODE_LALT);
                    } else if (!strcmp(attr.key, "ENTRY")){
                        key->setScancode(SDL_SCANCODE_BACKSPACE);
                    }
                     else if (!strcmp(attr.key, "F1")){
                        key->setScancode(SDL_SCANCODE_F1);
                    } else if (!strcmp(attr.key, "F2")){
                        key->setScancode(SDL_SCANCODE_F2);
                    } else if (!strcmp(attr.key, "F3")){
                        key->setScancode(SDL_SCANCODE_F3);
                    } else if (!strcmp(attr.key, "F4")){
                        key->setScancode(SDL_SCANCODE_F4);
                    } else if (!strcmp(attr.key, "F5")){
                        key->setScancode(SDL_SCANCODE_F5);
                    } else if (!strcmp(attr.key, "F6")){
                        key->setScancode(SDL_SCANCODE_F6);
                    } else if (!strcmp(attr.key, "F7")){
                        key->setScancode(SDL_SCANCODE_F7);
                    } else if (!strcmp(attr.key, "F8")){
                        key->setScancode(SDL_SCANCODE_F8);
                    } else if (!strcmp(attr.key, "F9")){
                        key->setScancode(SDL_SCANCODE_F9);
                    } else if (!strcmp(attr.key, "F10")){
                        key->setScancode(SDL_SCANCODE_F10);
                    } else if (!strcmp(attr.key, "F11")){
                        key->setScancode(SDL_SCANCODE_F11);
                    } else if (!strcmp(attr.key, "F12")){
                        key->setScancode(SDL_SCANCODE_F12);
                    } else {
                        key->setScancode(SDL_GetScancodeFromName(attr.value));
                    }
                } else if (!strcmp(attr.key, "command")){
                    key->setCommand(attr.value);
                } else if (!strcmp(attr.key, "type")){
                    if (!strcmp(attr.value, "key")){
                        key->setType(Tkey);
                    } else if (!strcmp(attr.value, "key up")){
                        key->setType(TkeyUp);
                    } else if (!strcmp(attr.value, "key down")){
                        key->setType(TkeyDown);
                    } else {
                        key->setType(Tkey);
                    }
            
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Keypad::read_xml, reason : cannot reconize '" << attr.key << "' key attribute" << endl;
                }
            }

            if (!key->is_empty() && push){
                this->keys.push_back(key);
            } else {
                delete key;
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Keypad::read_xml, reason : cannot reconize '" << child->tag << endl;
        }
    }

    return true;
}

bool Keypad::used_key(SDL_Scancode scancode){
    for (Key* key : this->keys){
        if (key->getScancode() == scancode){
            return true;
        }
    }
    return false;
}


Key* Keypad::getFromScancode(SDL_Scancode scancode){
    for (Key* key : this->keys){
        if (key->getScancode() == scancode){
            return key;
        }
    }
    return nullptr;
}