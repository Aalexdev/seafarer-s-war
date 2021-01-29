#include "main.hpp"

MainVar mainVar;

MainVar* getMain(){
    return &mainVar;
}

int main(int argc, char* argv[]){

    if (SDL_MAJOR_VERSION != 2){
        cerr << "ERROR :: cannot load missmatch SDL verion (" << SDL_MAJOR_VERSION << "!=2" << endl;
        return EXIT_FAILURE;
    }

    IS_DEBUG = false;

    TIME.now = time(0);
    TIME.ltm = localtime(&TIME.now);

    KEYPAD = new Keypad();
    mainVar.launched = readXML("data\\main.xml", false);

    while (mainVar.launched){

        TIME.startTick = SDL_GetTicks();

        event();
        update();
        draw();
        time();
    }

    destroy();

    return EXIT_SUCCESS;
}

void event(){
    SDL_Event e;

    if (SDL_PollEvent(&e)){
        switch (e.type){

            case SDL_QUIT:
                mainVar.launched = false;
                break;
            
            case SDL_MOUSEMOTION:
                mainVar.event.mouse.x = e.motion.x;
                mainVar.event.mouse.y = e.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button){
                    case SDL_BUTTON_LEFT:
                        MOUSEBTN.left = true;
                        MOUSEDOWN.left = true;
                        break;
                    
                    case SDL_BUTTON_MIDDLE:
                        MOUSEBTN.middle = true;
                        MOUSEDOWN.middle = true;
                        break;
                    
                    case SDL_BUTTON_RIGHT:
                        MOUSEBTN.right = true;
                        MOUSEDOWN.right = true;
                        break;
                        
                    default:
                        break;
                }
                break;
            
            case SDL_MOUSEBUTTONUP:
                switch (e.button.button){
                    case SDL_BUTTON_LEFT:
                        MOUSEBTN.left = false;
                        MOUSEUP.left = true;
                        break;
                    
                    case SDL_BUTTON_MIDDLE:
                        MOUSEBTN.middle = false;
                        MOUSEUP.left = true;
                        break;
                    
                    case SDL_BUTTON_RIGHT:
                        MOUSEBTN.right = false;
                        MOUSEUP.left = true;
                        break;
                        
                    default:
                        break;
                }
                break;
        }
        KEYPAD->event(e);
    }
}

void updateWidgets(void){
    for (TextButton* btn : WIDGETS.textButtons){
        if (btn) btn->update();
    }

    for (ImageButton* btn : WIDGETS.imageButtons){
        if (btn) btn->update();
    }

    for (SpriteButton* btn : WIDGETS.spriteButtons){
        if (btn) btn->update();
    }
}

void resetMouse(void){
    MOUSEUP.left = false;
    MOUSEUP.middle = false;
    MOUSEUP.right = false;

    MOUSEDOWN.left = false;
    MOUSEDOWN.middle = false;
    MOUSEDOWN.right = false;
}

void update(){
    int exec = SDL_GetTicks();

    updateWidgets();
    
    resetMouse();
    mainVar.time.updateExecT = SDL_GetTicks() - exec;
}

void drawWidgets(void){
    for (Text* text : WIDGETS.texts){
        if (text) text->draw();
    }

    for (TextButton* btn : WIDGETS.textButtons){
        if (btn) btn->draw();
    }

    for (ImageButton* btn : WIDGETS.imageButtons){
        if (btn) btn->draw();
    }

    for (SpriteButton* btn : WIDGETS.spriteButtons){
        if (btn) btn->drawButton();
    }
}

void drawLayers(int z){
    for (Layer* lyr : LAYERS){
        if (lyr->getZ() == z){
            lyr->draw();
        }
    }
}

void drawImages(void){
    for (Image* image : IMAGES){
        image->draw();
    }
}

void draw(){
    int exec = SDL_GetTicks();
    if (SDL_RenderClear(RENDERER)){
        if (IS_ERR_OPEN) ERR << "ERROR :: SDL_RenderClear(), reason : " << SDL_GetError << endl;
        mainVar.launched = false;
        return;
    }

    for (int i=-256; i<256; i++){
        drawLayers(i);
    }

    drawImages();
    drawWidgets();

    SDL_RenderPresent(RENDERER);
    mainVar.time.drawExecT = SDL_GetTicks() - exec;
}

void time(){

    if(SDL_GetTicks() < mainVar.time.tick+1000){
            mainVar.time._fps++;

    } else {
        mainVar.time.FPS = mainVar.time._fps;

        printf("FPS : %d\n", mainVar.time.FPS);

        mainVar.time.tick = SDL_GetTicks();
        mainVar.time._fps=0;
    }

    //fps limter
    int finnalTick = SDL_GetTicks();

    mainVar.time.execTime = (finnalTick - mainVar.time.startTick) > mainVar.time.maxDelay ? mainVar.time.maxDelay : (finnalTick - mainVar.time.startTick);
    SDL_Delay(mainVar.time.maxDelay-mainVar.time.execTime);
}

void freeFont(void){
    if(TTF_WasInit()){
        
        if (MAINVAR->font.font){
            if (IS_LOG_OPEN) LOG << "TTF_CloseFont()" << endl;
            TTF_CloseFont(MAINVAR->font.font);
        }

        if (IS_LOG_OPEN) LOG << "TTF_Quit()" << endl;
        TTF_Quit();
    }
}

void freeWindow(void){
    if (IS_LOG_OPEN) LOG << "SDL_DestroyRenderer()" << endl;
    if (MAINVAR->renderer) SDL_DestroyRenderer(MAINVAR->renderer);
    
    if (IS_LOG_OPEN) LOG << "SDL_DestroyWindow()" << endl;
    if (MAINVAR->window) SDL_DestroyWindow(MAINVAR->window);

    if (IS_LOG_OPEN) LOG << "SDL_Quit()" << endl;
    SDL_Quit();
}

void freeWidgets(void){
    if (IS_LOG_OPEN) LOG << "freeWidgets()" << endl;
    for (Text* text : WIDGETS.texts){
        if (text) delete text;
    }
    WIDGETS.texts.clear();

    for (TextButton* btn : WIDGETS.textButtons){
        if (btn) delete btn;
    }
    WIDGETS.textButtons.clear();

    for (ImageButton* btn : WIDGETS.imageButtons){
        if (btn) delete btn;
    }
    WIDGETS.imageButtons.clear();

    for (SpriteButton* btn : WIDGETS.spriteButtons){
        if (btn) delete btn;
    }
    WIDGETS.spriteButtons.clear();

    for (Image* image : IMAGES){
        delete image;
    }
    IMAGES.clear();
}

void destroy(void){

    freeWidgets();

    for (Layer* lyr : LAYERS){
        delete lyr;
    }
    LAYERS.clear();


    delete KEYPAD;

    freeFont();
    freeWindow();

    if (IS_LOG_OPEN) LOG.close();
    if (IS_ERR_OPEN) ERR.close();
}

void setLog(std::string path){
    mainVar.log_file = path;
}
void setErr(std::string path){
    mainVar.err_file = path;
}

bool loadLog(void){
    if (IS_LOG_OPEN) LOG.close();

    LOG.open(MAINVAR->log_file, ios::out);

    if (!LOG){
        cerr << "cannot load '" << MAINVAR->log_file << "' file" << endl;
        return false;
    }

    LOG << "LOG file, init at : " << HOURE << ":" << MINUTE << ":" << SECOND << endl;

    return true;
}

bool loadErr(void){
    if (IS_ERR_OPEN) ERR.close();

    ERR.open(MAINVAR->log_file, ios::out);

    if (!ERR){
        cerr << "cannot load '" << MAINVAR->err_file << "' file" << endl;
        return false;
    }

    ERR << "ERROR file, init at : " << HOURE << ":" << MINUTE << ":" << SECOND << endl;
    return true;
}

void closeLog(void){
    LOG.close();
}

void closeERR(void){
    ERR.close();
}

Point getMousePos(void){
    return (Point){MOUSE.x, MOUSE.y};
}
int windowWidth(void){
    int w, h;
    SDL_GetWindowSize(WINDOW, &w, &h);
    return w;
}

int windowHeight(void){
    int w, h;
    SDL_GetWindowSize(WINDOW, &w, &h);
    return h;
}