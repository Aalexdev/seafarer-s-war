#include "api/functions/texture.hpp"
#include "main.hpp"

SDL_Texture* loadTexture(std::string path, SDL_Rect* rect){
    path = DIR + path;
    if (IS_LOG_OPEN) LOG << "loadTexture(" << path << ")" << endl;
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (surface){
        SDL_Texture* texture = SDL_CreateTextureFromSurface(RENDERER, surface);
        SDL_FreeSurface(surface);
        if (texture){
            if (SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h) == 0){  
                return texture;
            } else {
                if (IS_ERR_OPEN) ERR << "ERROR :: SDL_QueryTexture, reason : " << SDL_GetError() << endl;
                cerr << "SDL_QueryTexture Error, reason : " << SDL_GetError() << endl;
            }
        } else {
            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_CreateTextureFromSurface, reason : " << SDL_GetError() << endl;
            cerr << "SDL_CreateTextureFromSurface Error, reason : " << SDL_GetError() << endl;
        }
    } else {
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_LoadBMP, reason : " << SDL_GetError() << endl;
        cerr << "SDL_LoadBMP Error, reason : " << SDL_GetError() << endl;
    }
    return NULL;
}

SDL_Texture* surfaceToTexture(SDL_Surface *surface, SDL_Rect *rect){
    if (surface){
        SDL_Texture* texture = SDL_CreateTextureFromSurface(RENDERER, surface);
        if (texture){
            if (SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h) == 0){
                return texture;
            } else {
                if (IS_ERR_OPEN) ERR << "ERROR :: SDL_QueryTexture, reason : " << SDL_GetError() << endl;
                cerr << "SDL_QueryTexture Error, reason : " << SDL_GetError() << endl;
            }
        } else {
            if (IS_ERR_OPEN) ERR << "ERROR :: SDL_CreateTextureFromSurface, reason :: " << SDL_GetError() << endl;
            cerr << "SDL_CreateTextureFromSurface Error, reason : " << SDL_GetError() << endl;
        }
    } else {
        if (IS_ERR_OPEN) ERR << "ERROR :: surfaceToTexture, reason : cannot load NULL surface" << endl;
        cerr << "cannot load a NULL surface" << endl;
    }
    return nullptr;
}

SDL_Texture* createRGBTexture(SDL_Color color, SDL_Rect rect){

    if (rect.w <= 0 && rect.h <= 0){
        if (IS_ERR_OPEN) ERR << "ERROR :: createRGBTexture, reason : 'cannot create a surface with 0 width or/and 0 height'" << endl;
        return nullptr;
    }

    if (IS_LOG_OPEN) LOG << "create a RGB surface" << endl;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, color.r, color.g, color.b, color.a);

    if (!surface){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_CreateRGBSurface, reason :: '" << SDL_GetError() << "'" << endl;
        return nullptr;
    }

    SDL_Texture* texture = surfaceToTexture(surface, &rect);
    SDL_FreeSurface(surface);

    if (!texture) return nullptr;

    return texture;
}

Image::Image(std::string path){
    this->set(path);
}
Image::Image(SDL_Color color){
    this->set(color);
}

Image::Image(Uint8 r, Uint8 g, Uint8 b){
    SDL_Color color = {r, g, b, 255};
    this->texture = createRGBTexture(color, this->rect);
}

Image::~Image(){
    if (this->texture) SDL_DestroyTexture(this->texture);
}

bool Image::set(std::string path){
    this->texture = loadTexture(path, &this->rect);

    if (this->texture) return true;
    return false;
}
bool Image::set(SDL_Color color){
    this->texture = createRGBTexture(color, this->rect);

    if (this->texture) return true;
    return false;
}
bool Image::set(Uint8 r, Uint8 g, Uint8 b){
    SDL_Color color = {r, g, b, 255};
    this->texture = createRGBTexture(color, this->rect);
    if (this->texture) return true;
    return false;
}

bool Image::draw(void){
    if (!this->texture) return false;

    if (SDL_RenderCopy(RENDERER, this->texture, NULL, &this->rect)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderCopy, reason : " << SDL_GetError() << endl;
        return false;
    }
    return true;
}

bool Image::read_from_xml(XMLNode* node){
    if (!node){
        if (IS_ERR_OPEN) ERR << "ERROR :: Image::read_from_xml, reason : cannot load a null node" << endl;
        return false;
    }

    this->rect = (SDL_Rect){0, 0, 0, 0};

    for(int a=0; a<node->attributes.size; a++){
        XMLAttribute attr = node->attributes.data[a];

        if (!strcmp(attr.key, "path")){
            this->set(attr.value);
        } else if (!strcmp(attr.key, "x")){
            sscanf(attr.value, "%d", &this->rect.x);
        } else if (!strcmp(attr.key, "y")){
            sscanf(attr.value, "%d", &this->rect.y);
        } else if (!strcmp(attr.key, "w")){
            if (!strcmp(attr.value, "fullscreen")){
                this->rect.w = windowWidth();
            } else {
                sscanf(attr.value, "%d", &this->rect.w);
            }
        } else if (!strcmp(attr.key, "h")){
            if (!strcmp(attr.value, "fullscreen")){
                this->rect.h = windowHeight();
            } else {
                sscanf(attr.value, "%d", &this->rect.h);
            }
        } else {
            if (IS_ERR_OPEN) ERR << "WARNING :: Image::read_from_xml, reason :: cannot reconize '" << attr.key << "' image attribute" << endl;
        }
    }
    return true;
}

bool Image::setAlpha(Uint8 alpha){
    if (SDL_SetTextureAlphaMod(this->texture, alpha)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_SetTextureAlphaMod, reason : " << SDL_GetError() << endl;
        return false;
    }
    return true;
}