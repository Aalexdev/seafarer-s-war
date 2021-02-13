#ifndef __MAIN__
#define __MAIN__

    #include <iostream>
    #include <fstream>
    #include <ctime>
    using namespace std;

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

    #include "api/io/setting.hpp"
    #include "api/const.hpp"
    #include "api/functions/math.hpp"
    #include "ui/graphics/sprite.hpp"
    #include "ui/widgets/text.hpp"
    #include "ui/debug.hpp"
    #include "ui/widgets/button.hpp"
    #include "ui/layer.hpp"
    #include "api/event/keypad.hpp"
    #include "api/functions/texture.hpp"
    #include "ui/widgets/textArea.hpp"
    #include "api/class/entity.hpp"

    struct Mods{
        bool debug;
    };

    struct MouseButton{
        bool left, middle, right;
    };

    struct Mouse{
        int x, y;

        MouseButton down;
        MouseButton up;
        MouseButton buttons;
    };

    struct Camera{
        int x, y;
    };

   struct Event{
       Mouse mouse;
       Keypad *keypad;
   };

    struct MainFont{
        TTF_Font* font;

        std::string fontPath;
        int size;
    };

    struct Time{
        int FPS;
        int _fps;

        int maxDelay;
        int maxFPS;

        long startTick, tick;
        int updateExecT, drawExecT, execTime;
        
        time_t now;
        tm *ltm;
    };

    struct Widgets{
        vector<Text*> texts;
        vector<Image*> images;
        vector<ImageButton*> imageButtons;
        vector<SpriteButton*> spriteButtons;
        vector<TextButton*> textButtons;
    };

    struct Player_control{
        SDL_Scancode engineUp;
        SDL_Scancode engineDown;

        SDL_Scancode turnLeft;
        SDL_Scancode turnRight;

        SDL_Scancode layerUp;
        SDL_Scancode layerDown;

        bool engineUP_type;
        bool engineDown_type;
        bool turnLeft_type;
        bool turnRight_type;
        bool layerUp_type;
        bool layerDown_type;
    };
    
    struct MainVar{
        SDL_Window* window;
        SDL_Renderer* renderer;

        bool isInit;
        bool launched;

        Time time;
        MainFont font;
        Event event;
        Mods mods;

        std::string log_file;
        std::string err_file;

        fstream log;
        fstream err;

        Sprite_list* spriteList;

        std::string mainDir;

        Widgets widgets;
        vector<Layer*> layers;
        Camera camera;

        vector<Entity*> entity;
        vector<Entity_type*> entity_types;
        
        float zoom;
        bool gamePause;

        Entity* player;

        Part_Type_list* part_list;

        Player_control playerKeys;
    };

    void setLog(std::string path);
    void setErr(std::string path);

    bool loadLog(void);
    bool loadErr(void);
    void closeLog(void);

    MainVar* getMain(void);

    // mainWhile functions

    void event(void);
    void update(void);
    void draw(void);
    void time(void);

    void destroy(void);

    // TTF
    void freeFont(void);

    // SDL
    void freeWindow(void);
    void freeWidgets(void);

    void freeEntity_types();
    void freeEntity();

    Point getMousePos(void);

    int windowWidth(void);
    int windowHeight(void);

    bool setIcon(std::string path);

    #define MAINVAR getMain()
    #define WINDOW getMain()->window
    #define RENDERER getMain()->renderer
    #define ISINIT getMain()->isInit
    #define TIME getMain()->time
    #define FONT getMain()->font
    #define EVENT getMain()->event
    #define MOUSE getMain()->event.mouse
    #define KEYPAD getMain()->event.keypad
    #define MOUSEPOS getMousePos()
    #define IS_DEBUG getMain()->mods.debug
    #define SPRITELIST getMain()->spriteList
    #define TICKS SDL_GetTicks()
    #define DIR getMainDir()
    #define WIDGETS getMain()->widgets
    #define MOUSEUP getMain()->event.mouse.up
    #define MOUSEDOWN getMain()->event.mouse.down
    #define MOUSEBTN getMain()->event.mouse.buttons
    #define LAYERS getMain()->layers
    #define LOG getMain()->log
    #define IS_LOG_OPEN getMain()->log.is_open()
    #define ERR getMain()->err
    #define IS_ERR_OPEN getMain()->err.is_open()
    #define SECOND getMain()->time.ltm->tm_sec
    #define MINUTE getMain()->time.ltm->tm_min
    #define HOURE getMain()->time.ltm->tm_hour
    #define DAY getMain()->time.ltm->tm_mday
    #define MONTH getMain()->time.ltm->tm_mon
    #define YEAR getMain()->time.ltm->tm_year
    #define CAMERA getMain()->camera
    #define IMAGES getMain()->widgets.images
    #define ENTITY getMain()->entity
    #define ENTITY_TYPES getMain()->entity_types
    #define ZOOM getMain()->zoom
    #define PAUSE getMain()->gamePause
    #define PLAYER getMain()->player
    #define PART_LIST getMain()->part_list
    #define PLAYER_CONTROL getMain()->playerKeys

#endif