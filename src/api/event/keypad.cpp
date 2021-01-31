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
void Key::setTag(std::string tag){
    this->tag = tag;
}
void Key::setCommand(std::string cmd){
    this->cmd = cmd;
}
SDL_Scancode Key::getScancode(void){
    return this->code;
}
void Key::update(void){
    switch (this->type){
        case Tkey:
            if (KEYPAD->getKey(this->code)) readXML(this->cmd, false);
            break;
        
        case TkeyUp:
            if (KEYPAD->getKeyUp(this->code)) readXML(this->cmd, false);
            break;
        
        case TkeyDown:
            if (KEYPAD->getKeyDown(this->code)) readXML(this->cmd, false);
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
            for (Key* key : this->keys){
                key->update();
            }
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
                    key->setScancode(SDL_GetScancodeFromName(attr.value));

                    if (used_key(key->getScancode())){
                        Key* temp = this->getFromScancode(key->getScancode());
                        delete temp;
                        temp = key;
                        push = false;
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