#include "ui/widgets/textArea.hpp"
#include "main.hpp"
#include "api/const.hpp"

TextArea::TextArea(){
    if (IS_LOG_OPEN) LOG << "TextArea::TextArea" << endl;
    this->text = new Text();
    this->background = new Image();
}
TextArea::~TextArea(){
    delete this->text;
    delete this->background;
}

bool TextArea::setBackground(string path){
    return this->background->set(path);
}
bool TextArea::setBackground(Uint8 r, Uint8 g, Uint8 b){
    return this->background->set(r, g, b);
}

void TextArea::setPos(int x, int y){
    this->setX(x);
    this->setY(y);
}

void TextArea::setSize(int w, int h){
    this->background->setSize(w, h);
}
void TextArea::setRect(SDL_Rect rect){
    this->background->setRect(rect);
}

void TextArea::setX(int x){
    this->background->setX(x);
    if (this->text->getW()) this->text->setX(x + (this->text->getW() / 2));
}

void TextArea::setY(int y){
    this->background->setY(y);
    if (this->text->getW()) this->text->setY(y + (this->text->getH() / 2));
}
void TextArea::setW(int w){
    this->background->setW(w);
}
void TextArea::setH(int h){
    this->background->setH(h);
}

void TextArea::lock(void){
    this->locked = true;
}
void TextArea::unlock(void){
    this->locked = false;
}

void TextArea::setMaxText(int maxSize){
    this->maxSize = maxSize;
}

bool TextArea::draw(void){
    if (!this->background->draw()) return false;
    if (!this->text->draw()) return false;
    if (IS_DEBUG){
        if (SDL_RenderDrawRect(RENDERER, this->background->getRect())){
            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawRect, reason : " << SDL_GetError() << endl;
            return false;
        }
    }
    return true;
}

void TextArea::update(void){
    if (pointInRect(MOUSEPOS, *this->background->getRect())){
        if (!this->write){
            this->background->setAlpha(255);
            this->text->setAlpha(255);
            this->write = true;
        }
    } else {
        if (this->write){
            this->background->setAlpha(150);
            this->text->setAlpha(150);
            this->write = false;
        }
    }
}

void TextArea::event(SDL_Event* e){
    if (!this->write) return;

    switch (e->type){
        case SDL_TEXTINPUT:
            if (!this->text->setText(this->text->getText() + e->text.text)) return;
            cout << this->text->getText().size() << endl;
            break;
        
        case SDL_KEYDOWN:
            switch (e->key.keysym.scancode){
                case 42:
                    if (!this->text->getText().empty()) this->text->setText(this->text->getText().erase(this->text->getText().size()));
                    break;
            }
            break;
        
        default:
            break;
    }
}

bool TextArea::read_from_xml(XMLNode* node){
    if (IS_LOG_OPEN) LOG << "TextArea::read_from_xml()" << endl;
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: TextArea::read_from_xml, reason : cannot read a null xml node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "x")){
            int x;
            sscanf(attr.value, "%d", &x);
            this->setX(x);
            this->background->setX(x);
        } else if (!strcmp(attr.key, "y")){
            int x;
            sscanf(attr.value, "%d", &x);
            this->setY(x);
            this->background->setY(x);
        } else if (!strcmp(attr.key, "w")){
            int x;
            sscanf(attr.value, "%d", &x);
            this->setW(x);
        } else if (!strcmp(attr.key, "h")){
            int x;
            sscanf(attr.value, "%d", &x);
            this->setH(x);
        } else if (!strcmp(attr.key, "background")){
            this->setBackground(attr.value);
        } else if (!strcmp(attr.key, "tag")){
            this->tag = attr.value;
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: TextArea::read_from_xml, reason : cannot reconize '" << attr.key << "' textArea attribute" << endl;
        }
    }

    return true;
}

string TextArea::getTag(void){
    return this->tag;
}

string TextArea::getText(void){
    return this->text->getText();
}