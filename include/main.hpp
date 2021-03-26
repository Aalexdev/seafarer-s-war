/**
 * @file main.hpp
 * @author @Aalexdev (aaleex394@gmail.com)
 * @brief the Entity file
 * @version 1.0.1
 * 
 * @copyright (c) 2021 Aalex
 * 
 * MIT License
 *
 *  Copyright (c) 2021 Aalex
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions: 
 * 
 * The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

/**
 * @file main.hpp
 * 
 * Header file for mainVar class and methode managment
 * 
 */
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
    #include "api/class/island.hpp"
    #include "api/class/equipment.hpp"
    #include "api/class/Ammunition.hpp"
    #include "api/types/Ammunition_type.hpp"
    #include "ui/graphics/particles.hpp"
    #include "ui/graphics/light.hpp"

    /**
     * @brief Struct of 
     * 
     */
    struct Mods{
        bool debug;
    };
    
    /**
     * @brief Struct of mouse's buttons
     * 
     */
    struct MouseButton{
        /**
         * @brief button of the mouse
         * 
         */
        bool left, middle, right;
    };

    /**
     * @brief the mouse struct with coords and buttons
     * 
     */
    struct Mouse{
        /**
         * @brief mouse's position on the window
         * 
         */
        int x, y;

        /**
         * @brief mouse button down event
         * 
         */
        MouseButton down;

        /**
         * @brief mouse button up event
         * 
         */
        MouseButton up;

        /**
         * @brief true whene the button is down, false otherwise
         * 
         */
        MouseButton buttons;
    };

    /**
     * @brief the strutc camera (position on the map)
     * 
     */
    struct Camera{
        /**
         * @brief x axis of the map position
         * 
         */
        int x;

        /**
         * @brief the y axis on the map
         * 
         */
        int y;
    };

   struct Event{
       /**
        * @brief var to a mouse struct
        * 
        */
       Mouse mouse;

       /**
        * @brief the keypad
        * 
        */
       Keypad *keypad;
   };

    struct MainFont{
        /**
         * @brief the font of the game
         * 
         */
        TTF_Font* font;
        
        /**
         * @brief the path to the font file
         * 
         */
        string fontPath;

        /**
         * @brief the size of the font
         * 
         */
        int size;
    };

    struct Time{
        /**
         * @brief frames per second
         * 
         */
        int FPS;

        /**
         * @brief fps counter
         * 
         */
        int _fps;

        /**
         * @brief maximal ticks beetween two frame
         * 
         */
        int maxDelay;

        /**
         * @brief maximal fps
         * 
         */
        int maxFPS;

        /**
         * @brief ticks
         * 
         */
        long startTick, tick;
        int updateExecT, drawExecT, execTime;
        
        /**
         * @brief real time
         * 
         */
        time_t now;
        tm *ltm;
        
    };

    /**
     * @brief widgets on the window
     * 
     */
    struct Widgets{
        /**
         * @brief texts vector
         * 
         */
        vector<Text*> texts;
        /**
         * @brief images vector
         * 
         */
        vector<Image*> images;

        /**
         * @brief imageButton vector
         * 
         */
        vector<ImageButton*> imageButtons;

        /**
         * @brief srpiteButton vector
         * 
         */
        vector<SpriteButton*> spriteButtons;

        /**
         * @brief textButton vector
         * 
         */
        vector<TextButton*> textButtons;
    };

    /**
     * @brief player keys
     * 
     */
    struct Player_control{
        /**
         * @brief key throttle up
         * 
         */
        SDL_Scancode engineUp;

        /**
         * @brief key throttle down
         * 
         */
        SDL_Scancode engineDown;
        SDL_Scancode turnLeft;
        SDL_Scancode turnRight;

        SDL_Scancode layerUp;
        SDL_Scancode layerDown;

        /**
         * @brief the type of the engineUP  key
         * 
         * false: sticky
         * true : push
         * 
         */
        bool engineUP_type;

        /**
         * @brief the type of the engineDown  key
         * 
         * false: sticky
         * true : push
         * 
         */
        bool engineDown_type;

        /**
         * @brief the type of the turnLeft  key
         * 
         * false: sticky
         * true : push
         * 
         */
        bool turnLeft_type;

        /**
         * @brief the type of the turnRight  key
         * 
         * false: sticky
         * true : push
         * 
         */
        bool turnRight_type;

        /**
         * @brief the type of the layerUp  key
         * 
         * false: sticky
         * true : push
         * 
         */
        bool layerUp_type;

        /**
         * @brief the type of the layerDown  key
         * 
         * false: sticky
         * true : push
         * 
         */
        bool layerDown_type;

        /**
         * @brief lights key event
         * 
         */
        SDL_Scancode lights;

        /**
         * @brief the light key types
         * 
         */
        bool light_type;
    };

    struct Files{
        /**
         * @brief the path of the file to load
         * 
         */
        string filePath;

        /**
         * @brief the last loaded file
         * 
         */
        string last_filePath;
    };

    struct Light_Edge{
        /**
         * @brief starting x and starting y
         * 
         */
        int sx, sy;

        /**
         * @brief ending x and ending y
         * 
         */
        int ex, ey;
    };
    
    struct MainVar{
        /**
         * @brief the window
         * 
         */
        SDL_Window* window;

        /**
         * @brief the rendere, linked with window
         * 
         */
        SDL_Renderer* renderer;

        /**
         * @brief true if the game loaded, false otherwise
         * 
         */
        bool isInit;

        /**
         * @brief the boolean value for the main while
         * 
         */
        bool launched;

        /**
         * @brief time struct
         * 
         */
        Time time;

        /**
         * @brief the font of text
         * 
         */
        MainFont font;

        /**
         * @brief events from the user, keypad and mouse
         * 
         */
        Event event;

        /**
         * @brief gamemodes
         * 
         */
        Mods mods;

        /**
         * @brief the path of the lag file
         * 
         */
        string log_file;

        /**
         * @brief the path of the error file
         * 
         */
        string err_file;

        /**
         * @brief the log file
         * 
         */
        fstream log;

        /**
         * @brief the error file
         * 
         */
        fstream err;

        /**
         * @brief the list of sprites types
         * 
         */
        Sprite_list* spriteList;

        /**
         * @brief the path of the directory
         * 
         */
        string mainDir;

        /**
         * @brief struct of widgets
         * 
         */
        Widgets widgets;

        /**
         * @brief layers of the screen
         * 
         */
        vector<Layer*> layers;

        /**
         * @brief the camera on the map (x and y)
         * 
         */
        Camera camera;

        /**
         * @brief the vector of entity in the game
         * 
         */
        vector<Entity*> entity;

        /**
         * @brief types of entity
         * 
         */
        vector<Entity_type*> entity_types;
        
        /**
         * @brief the zoom value
         * 
         */
        float zoom;

        /**
         * @brief true to pause the game
         * 
         */
        bool gamePause;

        /**
         * @brief the pointer of the player
         * 
         */
        Entity* player;

        /**
         * @brief struct of player controls
         * 
         */
        Player_control playerKeys;

        /**
         * @brief the list of ilands types
         * 
         */
        Island_type_list* Island_type_list;

        /**
         * @brief files struct
         * 
         */
        Files files;

        /**
         * @brief the z axis
         * 
         */
        int z;

        /**
         * @brief the size of the window
         * 
         */
        int windowWidth, windowHeight;

        /**
         * @brief 
         * 
         */
        vector<Equipment_type*> equipments;

        /**
         * @brief colors of the screen refresh
         * 
         */
        int r, g, b, a;

        /**
         * @brief the ammunition type vector
         * 
         */
        vector<Ammunition_type*> ammunitions_type; 
        
        /**
         * @brief the total time beetween two frame
         * 
         */
        int timeDelta;

        /**
         * @brief particles types
         * 
         */
        vector<Particles_type*> particles_type;

        /**
         * @brief particles
         * 
         */
        vector<Particles*> particles;

        /**
         * @brief type of lights
         * 
         */
        vector<Light_type*> lightTypes;

        /**
         * @brief lights
         * 
         */
        vector<Light*> lights;

        /**
         * @brief ammunitions
         * 
         */
        vector<Ammunition*> ammunitions;
    };

    /**
     * @brief Set the path of the log file
     * 
     * @param path the patg of the log file
     */
    void setLog(string path);

    /**
     * @brief Set the path of the error file
     * 
     * @param path the new path of error file
     */
    void setErr(string path);

    /**
     * @brief load the log file
     * 
     * @return * return true if loaded or created, false otherwise
     */
    bool loadLog(void);

    /**
     * @brief load the error file
     * 
     * @return * return true if loaded or created, false otherwise
     */
    bool loadErr(void);

    /**
     * @brief close the log file
     * 
     */
    void closeLog(void);

    /**
     * @brief close the error file
     * 
     */
    void closeErr(void);

    /**
     * @brief return the pointer of the mainVar struct
     * 
     * @return * return the mainVar struct 
     */
    MainVar* getMain(void);

    // mainWhile functions

    /**
     * @brief update events from the player
     * 
     */
    void event(void);

    /**
     * @brief update vars
     * 
     */
    void update(void);

    /**
     * @brief draw textures on the screen
     * 
     */
    void draw(void);

    /**
     * @brief update times value
     * 
     */
    void time(void);

    /**
     * @brief destroy textures, window, and renderer
     * 
     */
    void destroy(void);

    /**
     * @brief destroy the font
     * 
     */
    void freeFont(void);

    /**
     * @brief destroy the window
     * 
     */

    void freeWindow(void);
    /**
     * @brief destroy the renderer
     * 
     */
    void freeWidgets(void);

    /**
     * @brief destroy entity types
     * 
     */
    void freeEntity_types();

    /**
     * @brief destroy entity on the map
     * 
     */
    void freeEntity();

    /**
     * @brief Get the position of the mouse on the screen
     * 
     * @return Point 
     */
    Point getMousePos(void);

    /**
     * @brief get the width of teh window
     * 
     * @return * return the window's width     
     */
    int windowWidth(void);

    /**
     * @brief get the height of the window
     * 
     * @return * return the window's height 
     */
    int windowHeight(void);

    /**
     * @brief Set the icon of the window
     * 
     * @param path the patht to the .bmp image
     * @return * return true if loaded, false otherwise 
     */
    bool setIcon(string path);

    /**
     * @brief set the window refresh color
     * 
     * @param r the red color
     * @param g the green color
     * @param b the blue color
     */
    void SetColor(int r, int g, int b);

    /**
     * @brief set the window refresh color
     * 
     * @param r the red color
     * @param g the green color
     * @param b the blue color
     * @param a the alpha canal
     */
    void setColor(int r, int g, int b, int a);
    
    /**
     * @brief mainVar constant
     * 
     */
    #define MAINVAR         getMain()
    #define WINDOW          getMain()->window
    #define RENDERER        getMain()->renderer
    #define ISINIT          getMain()->isInit
    #define TIME            getMain()->time
    #define FONT            getMain()->font
    #define EVENT           getMain()->event
    #define MOUSE           getMain()->event.mouse
    #define KEYPAD          getMain()->event.keypad
    #define IS_DEBUG        getMain()->mods.debug
    #define SPRITELIST      getMain()->spriteList
    #define WIDGETS         getMain()->widgets
    #define MOUSEUP         getMain()->event.mouse.up
    #define MOUSEDOWN       getMain()->event.mouse.down
    #define MOUSEBTN        getMain()->event.mouse.buttons
    #define LAYERS          getMain()->layers
    #define LOG             getMain()->log
    #define IS_LOG_OPEN     getMain()->log.is_open()
    #define ERR             getMain()->err
    #define IS_ERR_OPEN     getMain()->err.is_open()
    #define SECOND          getMain()->time.ltm->tm_sec
    #define MINUTE          getMain()->time.ltm->tm_min
    #define HOURE           getMain()->time.ltm->tm_hour
    #define DAY             getMain()->time.ltm->tm_mday
    #define MONTH           getMain()->time.ltm->tm_mon
    #define YEAR            getMain()->time.ltm->tm_year
    #define CAMERA          getMain()->camera
    #define IMAGES          getMain()->widgets.images
    #define ENTITY          getMain()->entity
    #define ENTITY_TYPES    getMain()->entity_types
    #define ZOOM            getMain()->zoom
    #define PAUSE           getMain()->gamePause
    #define PLAYER          getMain()->player
    #define PLAYER_CONTROL  getMain()->playerKeys
    #define FILES           getMain()->files
    #define WINDOW_WIDTH    getMain()->windowWidth
    #define WINDOW_HEIGHT   getMain()->windowHeight
    #define WINDOW_AIR      getMain()->windowWidth * getMain()->windowHeight
    #define EQUIPMENTS      getMain()->equipments
    #define WINDOW_R        getMain()->r
    #define WINDOW_G        getMain()->g
    #define WINDOW_B        getMain()->b
    #define WINDOW_A        getMain()->a
    #define AMMUNITION_TYPE getMain()->ammunitions_type
    #define AMMUNITIONS     getMain()->ammunitions
    #define DELTA_TIME      getMain()->timeDelta
    #define PARTICLES_TYPE  getMain()->particles_type
    #define PARTICLES       getMain()->particles
    #define LIGHT_TYPES     getMain()->lightTypes
    #define LIGHTS          getMain()->lights
    #define MOUSEPOS        getMousePos()
    #define TICKS           SDL_GetTicks()
    #define DIR             getMainDir()
    #define NORTH           {0, 0, WINDOW_WIDTH, 0}
    #define NORTH_EAST      {WINDOW_WIDTH, 0}
    #define EAST            {WINDOW_WIDTH-1, 0, WINDOW_WIDTH-1, WINDOW_HEIGHT}
    #define SOUTH_EAST      {WINDOW_WIDTH, WINDOW_HEIGHT}
    #define SOUTH           {0, WINDOW_HEIGHT-1, WINDOW_WIDTH, WINDOW_HEIGHT-1}
    #define SOUTH_WEST      {0, WINDOW_HEIGHT}
    #define WEST            {0, 0, 0, WINDOW_HEIGHT}
    #define NORTH_WEST      {0, 0}
    
#endif