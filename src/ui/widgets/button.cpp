#include "ui/widgets/button.hpp"
#include "main.hpp"

bool ButtonClass::exec(void){
    if (IS_LOG_OPEN) LOG << "ButtonClass::exec()" << endl;

    if (!this) return true;
    if (this->cmd.empty()){
        if (IS_ERR_OPEN) ERR << "ERROR :: ButtonClass::exec, reason : cannot execute a empty file path" << endl;
        return false;
    }
    return readXML(this->cmd);
}

void TextButton::update(void){
    if (pointInRect(MOUSEPOS, this->getRect())){
        this->state = ButtonHover;
        if (MOUSEUP.left){
            this->state = ButtonPush;
            this->exec();
        }
    } else {
        this->state = ButtonNone;
    }
}

void ImageButton::update(void){
    if (pointInRect(MOUSEPOS, this->rect)){
        this->state = ButtonHover;
        if (MOUSEUP.left){
            this->state = ButtonPush;
            this->exec();
        }
    } else {
        this->state = ButtonHover;
    }
}

bool ImageButton::draw(void){
    if (this->texture){
        if (SDL_RenderCopy(RENDERER, this->texture, NULL, &this->rect)){
            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopy, reason : " << SDL_GetError() << endl;
            return false;
        }
    }
    return true;
}

void SpriteButton::update(void){
    if (pointInRect(MOUSEPOS, this->getRect())){
        this->state = ButtonHover;
        if (MOUSEUP.left){
            this->state = ButtonPush;
            this->exec();
        }
    } else {
        this->state = ButtonNone;
    }
}

bool SpriteButton::drawButton(void){
    if (this->is_Init()){
        
        if (this->state == ButtonNone){
            this->set_update(false);
        } else {
            this->set_update(true);
        }
        return this->draw();
    }
    if (IS_ERR_OPEN) ERR << "ERROR :: SpriteButton::drawButton, reason : cannot draw a sprite without type" << endl;
    return false;
}


bool ImageButton::read_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "ImageButton::read_from_xml" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: ImageButton::read_from_xml, reason :: cannot read a Button from a NULL node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "path")){
            this->texture = loadTexture(attr.value, &this->rect);
            if (!this->texture) return false;
        } else if (!strcmp(attr.key, "x")){
            sscanf(attr.value, "%d", &this->rect.x);
        } else if (!strcmp(attr.key, "y")){
            sscanf(attr.value, "%d", &this->rect.y);
        } else if (!strcmp(attr.key, "w")){
            sscanf(attr.value, "%d", &this->rect.w);
        } else if (!strcmp(attr.key, "h")){
            sscanf(attr.value, "%d", &this->rect.h);
        } else if (!strcmp(attr.key, "command")){
            this->cmd = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: ImageButton::read_from_xml, reason :: cannot reconize '" << attr.key << "' imageButton attribute" << endl; 
        }
    }
    return true;
}

bool TextButton::read_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "TextButton::read_from_xml()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: ImageButton::read_from_xml, reason :: cannot read a Button from a NULL node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "text")){
            if (!this->setText(attr.value)) return false;
        } else if (!strcmp(attr.key, "x")){
            int x=0;
            sscanf(attr.value, "%d", &x);
            this->setX(x);
        } else if (!strcmp(attr.key, "y")){
            int y;
            sscanf(attr.value, "%d", &y);
            this->setY(y);
        } else if (!strcmp(attr.key, "command")){
            if (IS_LOG_OPEN) LOG << "TextButton::cmd ('" << attr.value << "')" << endl;
            ButtonClass::cmd = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: ImageButton::read_from_xml, reason :: cannot reconize '" << attr.key << "' imageButton attribute" << endl; 
        }
    }
    return true;
}

bool SpriteButton::read_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "SpriteButton::read_from_xml()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: ImageButton::read_from_xml, reason :: cannot read a Button from a NULL node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "id")){
            int id=0;
            sscanf(attr.value, "%d", &id);
            if (!this->set(id)) return false;
        } else if (!strcmp(attr.key, "name")){
            if (!this->set(attr.value)) return false;
        } else if (!strcmp(attr.key, "x")){
            int x=0;
            sscanf(attr.value, "%d", &x);
            this->setX(x);
        } else if (!strcmp(attr.key, "y")){
            int y;
            sscanf(attr.value, "%d", &y);
            this->setY(y);
        } else if (!strcmp(attr.key, "command")){
            this->cmd = attr.value;
        } else if (!strcmp(attr.key, "duration")){
            int Tduration;
            sscanf(attr.value, "%d", &Tduration);
            this->set_duration(Tduration);
        } else if (!strcmp(attr.key, "w")){
            int w=0;
            sscanf(attr.value, "%d", &w);
            this->setW(w);
        } else if (!strcmp(attr.key, "h")){
            int h;
            sscanf(attr.value, "%d", &h);
            this->setH(h);
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: SpriteButton::read_from_xml, reason :: cannot reconize '" << attr.key << "' spriteButton attribute" << endl; 
        }
    }
    return true;
}