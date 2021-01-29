#include "ui/widgets/text.hpp"
#include "main.hpp"

Text::Text(){
    this->texture = nullptr;
    this->setPos(0, 0);
    this->setColor(255, 255, 255, 255);
}

Text::~Text(){
    if (this->texture){
        SDL_DestroyTexture(this->texture);
    }
}

bool Text::setText(std::string new_text){
    if (IS_LOG_OPEN) LOG << "Text::setText('" << new_text << "')" << endl;
    this->text = new_text;

    if (!TTF_WasInit()){
        if (IS_ERR_OPEN) ERR << "ERROR :: Text::setText, reason : cannot create a texture from text without init TTF engine" << endl;
        return false;
    }

    if (!FONT.font){
        if (IS_ERR_OPEN) ERR << "ERROR :: Text::setText, reason : cannot create a texture from text without font" << endl;
        return false;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(FONT.font, this->text.c_str(), this->color);
    
    if (!surface){
        if (IS_ERR_OPEN) ERR << "ERROR :: TTF_RenderText_Solide, reason : " << TTF_GetError << endl;
        return false;
    }

    int x = this->rect.x;
    int y = this->rect.y;

    this->texture = surfaceToTexture(surface, &this->rect);

    this->rect.x = x;
    this->rect.y = y;

    if (!this->texture){
        return false;
    }
    return true;
}

std::string Text::getText(void){
    return this->text;
}

bool Text::draw(void){
    if (SDL_RenderCopy(RENDERER, this->texture, NULL, &this->rect)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopy, reason : " << SDL_GetError() << endl;
        return false;
    }

    if (IS_DEBUG){
        SDL_SetRenderDrawColor(RENDERER, 255, 0, 0, 255);
        if (SDL_RenderDrawRect(RENDERER, &this->rect)){
            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderDrawRect, reason : " << SDL_GetError() << endl;
            return false;
        }
    }
    return true;
}

void Text::setPos(int x, int y){
    this->rect.x = x;
    this->rect.y = y;
}

void Text::setColor(Uint8 r, Uint8 g, Uint8 b){
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
}

bool Text::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->setColor(r, g, b);
    return this->setAlpha(a);
}


void Text::setColor(SDL_Color new_color){
    this->color = new_color;
    this->setText(this->text);
}

bool Text::setAlpha(Uint8 a){
    this->color.a = a;

    if (this->texture){
        if (SDL_SetTextureAlphaMod(this->texture, a)){
            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_SetTextureAlphaMod, reason : " << SDL_GetError() << endl;
            return false;
        }
    }
    return true;
}

Uint8 Text::getAlpha(void){
    return this->color.a;
}

bool Text::read_from_xml(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Text::read_from_xml, reason : cannot read null node" << endl;
        return false;
    }

    for (int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "x")){
            sscanf(attr.value, "%d", &this->rect.x);
        } else if (!strcmp(attr.key, "y")){
            sscanf(attr.value, "%d", &this->rect.y);
        } else if (!strcmp(attr.key, "text")){
            if (!this->setText(attr.value)) return false;
        } else {
            if (IS_ERR_OPEN) ERR << "ERROR :: Text::read_from_xml, reason  : cannot reconize '" << attr.key << "' text attribute" << endl;
        }
    }

    return true;
}