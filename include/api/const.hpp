#ifndef __CONST__
#define __CONST__

    #include "main.hpp"

    /**
     * @brief get the path to the appdata directory
     * 
     * @return return the AppData's path
     */
    string getAppData(void);

    /**
     * @brief get the size of the monitor
     * 
     * @param horizontal 
     * @param vertical 
     */
    void GetDesktopResolution(int& horizontal, int& vertical);

    /**
     * @brief get the directory of the executable
     * 
     * @return string 
     */
    string getCurrentDir(void);

    /**
     * @brief get the dirctory of seafarer's war
     * 
     * @return string 
     */
    string getMainDir(void);
    
    /**
     * @brief the AppData dirctory path
     * 
     */
    #define APPDATA getAppData()

    /**
     * @brief the version of the game
     * 
     */
    #define VERSION "0.0-2"

    /**
     * @brief the undefined value
     * 
     */
    #define UNDEFINE 71673

    /**
     * @brief the exectuable path
     * 
     */
    #define GETDIR getCurrentDir()

#endif