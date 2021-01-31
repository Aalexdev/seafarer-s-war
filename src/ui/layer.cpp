#include "ui/layer.hpp"
#include "main.hpp"

LayerTexture::LayerTexture(){
    this->texture = nullptr;
    this->alpha = 255;

    this->rect = (SDL_Rect){0, 0, 0, 0};
    this->addingPos = (SDL_Point){0, 0};
}

LayerTexture::~LayerTexture(){
    if (this->texture) SDL_DestroyTexture(this->texture);
}

bool LayerTexture::draw(void){
    if (!this->texture){
        if (IS_ERR_OPEN) ERR << "ERROR :: LayerTexture::draw, reason : cannot draw a null texture" << endl;
        return false;
    }

    if (SDL_RenderCopy(RENDERER, this->texture, NULL, &this->rect)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopy, reason : " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

Layer::Layer(void){
    this->textures.clear();
    this->timer = 0;
    this->delay = 0;
}
Layer::~Layer(){

    for (LayerTexture* texture : this->textures){
        delete texture;
    }

    this->textures.clear();
    this->name.clear();
}

bool Layer::read_from_xml(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: layer::read_from_xml, reason : cannot read a null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "name")){
            this->name = attr.value;
        } else if (!strcmp(attr.key, "id")){
            sscanf(attr.value, "%d", &this->id);
        } else if (!strcmp(attr.key, "angle")){
            sscanf(attr.value, "%d", &this->angle);
        } else if (!strcmp(attr.key, "delay")){
            sscanf(attr.value, "%d", &this->delay);
        } else if (!strcmp(attr.key, "height")){
            sscanf(attr.value, "%d", &this->z);
        } else if (!strcmp(attr.key, "speed")){
            sscanf(attr.value, "%d", &this->speed);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Layer::read_from_xml, reason : cannot reconize '" << attr.key << "' layer attribute" << endl;
        }
    }

    setAngleM(&this->addX, &this->addY, this->speed, this->angle);

    for (int c=0; c<node->children.size; c++){
        XMLNode* child = XMLNode_child(node, c);

        if (!strcmp(child->tag, "image")){
            LayerTexture* texture = new LayerTexture();

            for (int a=0; a<child->attributes.size; a++){
                XMLAttribute attr = child->attributes.data[a];

                if (!strcmp(attr.key, "path")){
                    texture->texture = loadTexture(attr.value, &texture->rect);

                    if (!texture->texture){
                        delete texture;
                        break;
                    }
                } else if (!strcmp(attr.key, "alpha")){
                    sscanf(attr.value, "%d", &texture->alpha);
                } else {
                    if (IS_ERR_OPEN) ERR << "WARNING :: Layer::read_from_xml, cannot reconize '" << attr.key << "' image attribute" << endl;
                }
            }

            if (texture->texture){
                if (SDL_SetTextureAlphaMod(texture->texture, texture->alpha)){
                    if (IS_ERR_OPEN) ERR << "ERROR :: SDL_SetTextureAlphaMod, reason : " << SDL_GetError() << endl;
                    delete texture;
                } else {
                    this->textures.push_back(texture);
                }
            } else {
                delete texture;
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Layer::read_from_xml, cannot reconize '" << child->tag << "' layer child" << endl;
        }
    }

    return true;
}

bool Layer::draw(void){
    if (this->textures.empty()) return true;

    for (LayerTexture* texture : this->textures){

        if (SDL_GetTicks() - this->delay >= this->timer){

            this->timer = SDL_GetTicks();

            texture->addingPos.y += this->addY;
            texture->addingPos.x += this->addX;

            if (texture->addingPos.y >= texture->rect.h) texture->addingPos.y = 0;
            
            if (texture->addingPos.x >= texture->rect.w) texture->addingPos.x = 0;
        }

        for (int y= -texture->rect.h - (CAMERA.y % texture->rect.h) / ZOOM + texture->addingPos.y - texture->rect.h; y < windowHeight()+texture->rect.h + (CAMERA.y % texture->rect.h) + texture->addingPos.y; y+=texture->rect.h / ZOOM){
            for (int x= -texture->rect.w - (CAMERA.x % texture->rect.w) / ZOOM + texture->addingPos.x - texture->rect.w; x < windowWidth()+texture->rect.w + (CAMERA.x % texture->rect.w) + texture->addingPos.x; x+=texture->rect.w / ZOOM){
                
                texture->rect.x = x+texture->addingPos.x;
                texture->rect.y = y+texture->addingPos.y;
                
                texture->draw();
                
            }
        }
    }

    return true;
}