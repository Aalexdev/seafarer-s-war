#include "ui/graphics/sprite.hpp"
#include "main.hpp"

Sprite_type::Sprite_type(){
    if (IS_LOG_OPEN) LOG << "Sprite_type::Sprite_type()" << endl;

    this->sprite = nullptr;
    this->isLoaded = false;
    this->children.clear();
}

Sprite_type::~Sprite_type(){
    if (IS_LOG_OPEN) LOG << "Sprite_type::~Sprite_type" << endl;

    if (this->sprite) SDL_DestroyTexture(this->sprite);
    this->children.clear();
}

bool Sprite_type::load_from_xml(XMLNode* node){

    if (IS_LOG_OPEN) LOG << "Sprite_type::load_from_xml" << endl;

    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite::load_from_xml, reason : cannot load a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            this->name = attr.value;
        } else if (!strcmp(attr.key, "id")){
            sscanf(attr.value, "%d", &this->id);
        } else if (!strcmp(attr.key, "image")){
            this->sprite = loadTexture(attr.value, &this->dstRect);
            if (!this->sprite){
                return false;
            }
        } else if (!strcmp(attr.key, "width")){
            sscanf(attr.value, "%d", &this->width);
        } else if (!strcmp(attr.key, "height")){
            sscanf(attr.value, "%d", &this->height);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Sprite_type::load_from_xml, reason :: cannot reconize '" << attr.key << "' sprite attribute" << endl;
        }
    }
    return this->reload();
}

bool Sprite_type::reload(void){

    if (IS_LOG_OPEN) LOG << "Sprite_type::reload" << endl;
    
    if (!this->sprite){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_type::reload, reason : cannot reload a null sprite image" << endl;
        return false;
    }

    if (this->dstRect.w <= 0){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_type::reload, reason : cannot reaload a sprite without image width" << endl;
        return false;
    }

    if (this->dstRect.h <= 0){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_type::reload, reason : cannot reload a sprite without image height" << endl;
        return false;
    }

    int x=0, y=0;

    while (true){
        Sprite_child* child = new Sprite_child();

        child->setX(x);
        child->setY(y);
        child->setW(this->width);
        child->setH(this->height);

        this->children.push_back(child);

        x += this->width;

        if (x >= this->dstRect.w){
            y += this->height;
            x = 0;
        }

        if (y >= this->dstRect.h){
            break;
        }
    }

    return true;
}

SDL_Rect Sprite_type::getIndex(int index){
    if (this->children.size() <= index){
        if (IS_ERR_OPEN) ERR << "WARNING :: Sprite_type::getIndex, reason : the input index is greater than the sprite" << endl;
        index = this->children.size() - 1;
    }
    SDL_Rect output = this->children[index]->getRect();

    return output;
}

bool Sprite_list::read_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "Sprite_list::read_from_xml" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_list::read_from_xml, reason : cannot load a null XMLNode" << endl;
        return false;
    }

    for (int c=0; c<node->children.size; c++){
        XMLNode* sprite = XMLNode_child(node, c);

        if (!strcmp(sprite->tag, "sprite")){
            Sprite_type *type = new Sprite_type();
            if (type->load_from_xml(sprite)){
                this->children.push_back(type);
            } else {
                delete type;
            }
        } else {
            if (IS_ERR_OPEN) ERR << "ERROR :: cannot reconize '" << sprite->tag << "' sprites children" << endl;
        }
    }
    return true;
}

Sprite_type* Sprite_list::search(string name){
    if (IS_LOG_OPEN) LOG << "Sprite_list::search(" << name << ")" << endl;
    
    
    if (this->children.empty()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_list::search, reason : cannot search a type in a empty list" << endl;
        return nullptr;
    }
    
    for (Sprite_type* type : this->children){
        if (type->getName() == name){
            return type;
        }
    }

    if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_list::search, reason : cannot found '" << name << "' type name" << endl;
    return nullptr;
}
Sprite_type* Sprite_list::search(int id){
    if (IS_LOG_OPEN) LOG << "Sprite_list::search(" << id << ")" << endl;
    if (this->children.empty()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_list::search, reason : cannot search a type in a empty list" << endl; 
        return nullptr;
    }

    for (Sprite_type* type : this->children){
        if (type->get_id() == id){
            return type;
        }
    }
    
    if (IS_ERR_OPEN) ERR << "ERROR :: Sprite_list::search, reason : cannot found '" << id << "' type name" << endl;
    return nullptr;
}

Sprite::Sprite(Sprite_list* list) : list(list){
    this->type = nullptr;
    this->duration = 0;
    this->angle = 0;
    this->index = 0;
    this->ticks = 0;
    this->update = true;
}

Sprite::Sprite(){
    this->list = nullptr;
    this->type = nullptr;
    this->duration = 0;
    this->angle = 0;
    this->index = 0;
    this->ticks = 0;
    this->update = true;
}

Sprite::~Sprite(){
    this->duration = 0;
    this->ticks = 0;
    this->type = 0;
    this->list = 0;
    this->index = 0;
}

void Sprite::setList(Sprite_list* list){
    this->list = list;
}

bool Sprite::set(int id){
    if (IS_LOG_OPEN) LOG << "Sprite::set(" << id << ")" << endl;
    if (!this->list){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite::set, reason : cannot set a sprite without list" << endl;
        return false;
    }

    this->type = this->list->search(id);

    if (!this->type) return false;
    return true;
}
bool Sprite::set(string name){
    if (IS_LOG_OPEN) LOG << "Sprite::set(" << name << ")" << endl;
    if (!this->list){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite::set, reason : cannot set a sprite without list" << endl;
        return false;
    }

    this->type = this->list->search(name);

    if (!type) return false;
    return true;
}

void Sprite::set(Sprite_type* type){
    if (IS_LOG_OPEN) LOG << "Sprite::set(Sprite_type* type)" << endl;
    this->type = type;
}

Sprite_type* Sprite::get_type(void){
    if (IS_LOG_OPEN) LOG << "Sprite::get_type" << endl;
    return this->type;
}

int Sprite::get_id(void){
    if (IS_LOG_OPEN) LOG << "Sprite::get_id" << endl;
    if (this->type){
        return this->type->get_id();
    }
    return 0;
}

string Sprite::get_name(void){
    if (IS_LOG_OPEN) LOG << "sprite::get_name" << endl;
    if (this->type){
        return this->type->getName();
    }
    return "";
}

bool Sprite::draw(void){
    if (!this->type){
        if (IS_ERR_OPEN) ERR << "ERROR :: sprite::draw, reason : cannot draw a sprite without image" << endl;
        return false;
    }

    if (this->update){
        if (SDL_GetTicks() - this->duration >= this->ticks){
            this->ticks = SDL_GetTicks();
            this->index++;

            if (this->index >= this->type->getSize()){
                this->index = 0;
            }
        }
    }

    SDL_Rect tempRect = this->type->getIndex(this->index);
    if (SDL_RenderCopyEx(RENDERER, this->type->getTexture(), &tempRect, &this->rect, this->angle, 0, SDL_FLIP_NONE)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopyEx, reason : " << SDL_GetError() << endl;
    }

    return true;
}

bool Sprite::is_Init(void){
    return (this->type);
}

bool Sprite::read_from_xml(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Sprite::read_from_xml, reason : cannot read a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "x")){
            sscanf(attr.value, "%d", &this->rect.x);
        } else if (!strcmp(attr.key, "y")){
            sscanf(attr.value, "%d", &this->rect.y);
        } else if (!strcmp(attr.key, "w")){
            sscanf(attr.value, "%d", &this->rect.w);
        } else if (!strcmp(attr.key, "h")){
            sscanf(attr.value, "%d", &this->rect.h);
        } else if (!strcmp(attr.key, "duration")){
            sscanf(attr.value, "%d", &this->duration);
        } else if (!strcmp(attr.value, "id")){
            int id;
            sscanf(attr.value, "%d", &id);
            this->type = this->list->search(id);
        } else if (!strcmp(attr.key, "name")){
            this->type = this->list->search(attr.value);
        }
    }
    return true;
}