#include "api/io/setting.hpp"
#include "api/io/xml.hpp"

#include "ui/main_window.hpp"

#include <SDL2/SDL_thread.h>

bool equal(char* a, const char* b){
    if (!strcmp(a, b))
        return true;
    return false;
}

bool charToBool(string str){
    if (str == "true") return true;
    return false;
}

bool readXML(string path){

    bool check = false;
    XMLDocument doc;

    
    path = DIR + path;

    if (IS_LOG_OPEN) LOG << "readXML(" << path << " , " << check << ")" << endl;


    if (XMLDocument_load(&doc, path.c_str())){

        for (int m=0; m<doc.root->children.size; m++){
            XMLNode* mainNode = XMLNode_child(doc.root, m);

            if (equal(mainNode->tag, "window")){

                int x, y, w, h;
                string title;

                if (MAINVAR->isInit){
                    SDL_GetWindowPosition(WINDOW, &x, &y);
                    SDL_GetWindowSize(WINDOW, &w, &h);
                }

                for (int c=0; c<mainNode->children.size; c++){
                    XMLNode* child = XMLNode_child(mainNode, c);

                    if (equal(child->tag, "size")){
                        for (int a=0; a<child->attributes.size; a++){
                            XMLAttribute attr = child->attributes.data[a];

                            if (equal(attr.key, "w")){
                                if (!check) sscanf(attr.value, "%d", &w);
                            }
                            else if (equal(attr.key, "h")){
                                if (!check) sscanf(attr.value, "%d", &h);
                            }
                            else{
                                if (IS_ERR_OPEN) ERR << "WARNING :: cannot reconize '" << attr.key << "' window attribute in '" << path << "' xml file" << endl;
                                cout << "WARNING :: cannot reconize '" << attr.key << "' window size attribute" << endl;
                            }
                        }
                    }
                    else if (equal(child->tag, "pos")){
                        for (int a=0; a<child->attributes.size; a++){
                            XMLAttribute attr = child->attributes.data[a];

                            if (equal(attr.key, "x")){
                                if (!check){
                                    if (equal(attr.value, "centered")){
                                        x = SDL_WINDOWPOS_CENTERED;
                                    } else {
                                        sscanf(attr.value, "%d", &x);
                                    }
                                }
                            }
                            else if (equal(attr.key, "y")){
                                if (!check){
                                    if (equal(attr.value, "centered")){
                                        y = SDL_WINDOWPOS_CENTERED;
                                    } else {
                                        sscanf(attr.value, "%d", &y);
                                    }
                                }
                            }
                            else{
                                if (IS_ERR_OPEN) ERR << "WARNING :: cannot reconize '" << attr.key << "' window attribute in '" << path << "' xml file" << endl;
                                cout << "WARNING :: cannot reconize '" << attr.key << "' window size attribute" << endl;
                            }
                        }

                        if (IS_LOG_OPEN){
                            string tempX, tempY;

                            if (x == 805240832){
                                tempX = "centered";
                            } else {
                                tempX = x;
                            }

                            if (y == 805240832){
                                tempY = "centered";
                            } else {
                                tempY = y;
                            }
                        }
                    }
                    else if (equal(child->tag, "title")){
                        for (int a=0; a<child->attributes.size; a++){
                            XMLAttribute attr = child->attributes.data[a];

                            if (equal(attr.key, "title")){
                                if (!check){
                                    title = attr.value;
                                }
                            }
                            else{
                                if (IS_ERR_OPEN) ERR << "WARNING :: cannot reconize '" << attr.key << "' window size attribute in '" << path << "' xml file" << endl;
                                cout << "WARNING :: cannot reconize '" << attr.key << "' window size attribute" << endl;
                            }
                        }
                    } else if (equal(child->tag, "flags")){
                        Uint32 flag = -1;
                        for (int a=0; a<child->attributes.size; a++){
                            XMLAttribute attr = child->attributes.data[a];

                            if (equal(attr.key, "display")){
                                if (equal(attr.value, "windowed")){
                                    flag = 0;
                                } else if (equal(attr.value, "fullscreen")){
                                    flag = SDL_WINDOW_FULLSCREEN;
                                } else if (equal(attr.value, "fullscreen auto")){
                                    flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
                                }
                            } else {
                                if (IS_ERR_OPEN) ERR << "ERROR :: readXML, reason : cannot reconize '" << attr.key << "' window flags attribute in " << path << endl;
                            }
                        }

                        if (flag != -1 && WINDOW){
                            if (SDL_SetWindowFullscreen(WINDOW, flag)){
                                if (IS_ERR_OPEN) ERR << "ERROR :: readXML, reason : " << SDL_GetError() << endl;
                                XMLDocument_free(&doc);
                                return false;
                            }
                        }
                    } else if (!strcmp(child->tag, "icon")){
                        for (int a=0; a<child->attributes.size; a++){
                            XMLAttribute attr = child->attributes.data[a];

                            if (!strcmp(attr.key, "path")){
                                setIcon(attr.value);
                            } else {
                                if (IS_ERR_OPEN) ERR << "WARNING :: radXML, reason : cannot reconize '" << attr.value << "' icon attribute" << endl;
                            }
                        }
                    }
                    else{
                        if (IS_ERR_OPEN) ERR << "WARNING :: cannot reconize '" << child->tag << "' window child in '" << path << "' xml file" << endl;
                        cout << "WARNING :: cannot reconize '" << child->tag << "' window child" << endl;
                    }
                }

                if (!check){
                    if (ISINIT){
                        if (IS_LOG_OPEN) LOG << "SDL_SetWindowPosition(" << x << ", " << y << ")" << endl;
                        SDL_SetWindowPosition(WINDOW, x, y);

                        if (IS_LOG_OPEN) LOG << "SDL_SetWindowSize(" << w << ", " << h << ")" << endl;
                        SDL_SetWindowSize(WINDOW, w, h);
                        WINDOW_WIDTH = w;
                        WINDOW_HEIGHT = h;
                        

                        if (!title.empty()){
                            if (IS_LOG_OPEN) LOG << "SDL_SetWindowTitle(" << title << ")" << endl;
                            SDL_SetWindowTitle(WINDOW, title.c_str());
                        }
                    } else {
                        if (!resteWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN)){
                            XMLDocument_free(&doc);
                            return false;
                        }
                    }
                }
            }
            else if (equal(mainNode->tag, "fps")){
                for (int c=0; c<mainNode->attributes.size; c++){
                    XMLAttribute attr = mainNode->attributes.data[c];

                    if (equal(attr.key, "limiter")){
                        if (!check){
                            sscanf(attr.value, "%d", &TIME.maxFPS);
                            TIME.maxDelay = 1000 / TIME.maxFPS;

                            if (IS_LOG_OPEN) LOG << "set max fps to : " << TIME.maxFPS << endl;;
                        }
                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING :: cannot reconize '" << attr.key << "' fps attribute in '" << path << "' xml file" << endl;
                    }
                }
            }
            else if (equal(mainNode->tag, "logs")){
                for (int a=0; a<mainNode->attributes.size; a++){
                    XMLAttribute attr = mainNode->attributes.data[a];

                    if (equal(attr.key, "log")){
                        if (!check){
                            setLog(DIR + attr.value);
                            loadLog();
                        }
                        
                    } else if (equal(attr.key, "error")){
                        if (!check){
                            setLog(DIR + attr.value);
                            loadErr();
                        }
                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING :: readXML, reason : cannot reconize '" << attr.key << "' log attribute in " << path << endl;
                        cout << "cannot reconize '" << attr.key << "logs attribute" << endl;
                    }
                }
            }
            else if (equal(mainNode->tag, "font")){
                if (IS_LOG_OPEN) LOG << "load font" << endl;

                if (!check){
                    if (!TTF_WasInit()){
                        if (IS_LOG_OPEN) LOG << "TTF_Init()" << endl;
                        if (TTF_Init() != 0){
                            if (IS_ERR_OPEN) ERR << "ERROR :: TTF_Init(), reason : " << TTF_GetError << endl;
                            cerr << "TTF_Init() Error, reason : " << TTF_GetError << endl;
                            XMLDocument_free(&doc);
                            return false;
                        }
                    }
                }

                for (int a=0; a<mainNode->attributes.size; a++){
                    XMLAttribute attr = mainNode->attributes.data[a];
                    if (!strcmp(attr.key, "path")){
                        if (!check){
                            FONT.fontPath = DIR;
                            FONT.fontPath += attr.value;
                        }
                    }
                    else if (!strcmp(attr.key, "size")){
                        if (!check){
                            sscanf(attr.value, "%d", &FONT.size);
                        }
                    }
                    else {
                        cout << "cannot reconize '" << attr.key << "' font attribute" << endl;
                        if (IS_ERR_OPEN) ERR << "WARNING :: cannot reconize '" << attr.key << "' font attribute in '" << path << "' xml file" << endl; 
                    }
                }

                if (FONT.font){
                    if (IS_LOG_OPEN) LOG << "TTF_CloseFont" << endl;
                    TTF_CloseFont(FONT.font);
                }

                if (IS_LOG_OPEN) LOG << "TTF_OpenFont(" << FONT.fontPath << " , " << FONT.size << ")" << endl;
                FONT.font = TTF_OpenFont(FONT.fontPath.c_str(), FONT.size);
            } else if (equal(mainNode->tag, "sprites")){
                if (!SPRITELIST){
                    SPRITELIST = new Sprite_list();
                }
                if (!SPRITELIST->read_from_xml(mainNode)){
                    delete SPRITELIST;
                    SPRITELIST = nullptr;
                }
            } else if (equal(mainNode->tag, "clearWidgets/") || equal(mainNode->tag, "clearWidgets")){
                freeWidgets();
            } else if (equal(mainNode->tag, "text")){
                Text* text = new Text();

                if (text->read_from_xml(mainNode)){
                    WIDGETS.texts.push_back(text);
                } else {
                    delete text;
                }
            } else if (equal(mainNode->tag, "imageButton")){
                ImageButton* btn = new ImageButton();

                if (btn->read_from_xml(mainNode)){
                    WIDGETS.imageButtons.push_back(btn);
                } else {
                    delete btn;
                }
            } else if (equal(mainNode->tag, "textButton")){
                TextButton* btn = new TextButton();

                if (btn->read_from_xml(mainNode)){
                    WIDGETS.textButtons.push_back(btn);
                } else {
                    delete btn;
                }
            } else if (equal(mainNode->tag, "spriteButton")){
                SpriteButton* btn = new SpriteButton();

                btn->setList(SPRITELIST);
                if (btn->read_from_xml(mainNode)){
                    WIDGETS.spriteButtons.push_back(btn);
                } else {
                    delete btn;
                }
            } else if (equal(mainNode->tag, "image")){
                Image* image = new Image();

                if (image->read_from_xml(mainNode)){
                    IMAGES.push_back(image);
                } else {
                    delete image;
                }
            } else if (equal(mainNode->tag, "read")){
                for (int a=0; a<mainNode->attributes.size; a++){
                    XMLAttribute attr = mainNode->attributes.data[a];

                    if (equal(attr.key, "path")){
                        if (!check){
                            readXML(attr.value);
                        }
                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING :: readXML, reason : cannot reconize '" << attr.key << "' readattribute in " << path << endl;
                    }
                }
            } else if (equal(mainNode->tag, "debug") || equal(mainNode->tag, "debug/")){
                if (IS_DEBUG){
                    IS_DEBUG = false;
                } else {
                    IS_DEBUG = true;
                }
            } else if (equal(mainNode->tag, "quit") || equal(mainNode->tag, "quit/")){
                MAINVAR->launched = false;
                XMLDocument_free(&doc);
                return false;
            } else if (equal(mainNode->tag, "layers")){
                for (int c=0; c<mainNode->children.size; c++){
                    XMLNode* layer = XMLNode_child(mainNode, c);

                    if (equal(layer->tag, "layer")){
                        Layer* lyr = new Layer();

                        if (lyr->read_from_xml(layer)){
                            LAYERS.push_back(lyr);
                        } else {
                            delete lyr;
                        }
                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING, readXML, cannot reconize '" << layer->tag << "' layers child" << endl;
                    }
                }
            } else if (equal(mainNode->tag, "onKey")){
                KEYPAD->read_xml(mainNode);
            } else if (equal(mainNode->tag, "entity")){
                Entity_type* type = new Entity_type();

                if (type->load_from_xml(mainNode)){
                    ENTITY_TYPES.push_back(type);
                } else {
                    delete type;
                }
            } else if (equal(mainNode->tag, "clearlogs")){
                loadLog();
                loadErr();
            } else if (equal(mainNode->tag, "write")){
                for (int a=0; a<mainNode->attributes.size; a++){
                    XMLAttribute attr = mainNode->attributes.data[a];

                    if (!strcmp(attr.key, "log")){
                        if (IS_LOG_OPEN) LOG << attr.value << endl;
                    } else if (!strcmp(attr.key, "err")){
                        if (IS_ERR_OPEN) ERR << attr.value << endl;
                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING :: readXML, cannot reconize '" << attr.key << "' write attribute" << endl;
                    }
                }
            } else if (equal(mainNode->tag, "summonEntity")){
                Entity* entity = new Entity(false);

                if (entity->load_from_xml(mainNode)){
                    ENTITY.push_back(entity);
                } else {
                    delete entity;
                }
            } else if (equal(mainNode->tag, "setPlayer")){
                PLAYER->load_from_xml(mainNode);

            } else if (equal(mainNode->tag, "clearEntitys/") || equal(mainNode->tag, "clearEntitys")){
                freeEntity();
            } else if (equal(mainNode->tag, "game")){
                for (int a=0; a<mainNode->attributes.size; a++){
                    XMLAttribute attr = mainNode->attributes.data[a];

                    if (!strcmp(attr.key, "pause")){
                        if (IS_LOG_OPEN) LOG << "pause()" << endl;
                        PAUSE = charToBool(attr.value);
                    } else {
                        if (IS_ERR_OPEN) ERR << "WARNING :: readXML, reason : cannot reconize '" << attr.key << "' game attribute" << endl;
                    }
                }
            } else if (equal(mainNode->tag, "equipment")){
                Equipment_type* e = new Equipment_type();

                if (e->loadXML(mainNode)){
                    EQUIPMENTS.push_back(e);
                } else {
                    delete e;
                }
            } else {
                if (IS_ERR_OPEN) ERR << "WARNING :: readXML, reason : cannot reconize '" << mainNode->tag << "' in " << path << endl;
            }
        }

    } else {
        if (IS_LOG_OPEN) LOG << "ERROR :: cannot load '" << path << "' xml file";
        cerr << "ERROR :: cannot load '" << path << "xml file" << endl;
        return false;
    }

    XMLDocument_free(&doc);
    return true;
}