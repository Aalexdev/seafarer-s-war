#ifndef __CONST__
#define __CONST__

    #include "main.hpp"

    string getAppData(void);
    void GetDesktopResolution(int& horizontal, int& vertical);
    string getCurrentDir(void);
    string getMainDir(void);
    
    #define APPDATA getAppData()
    #define VERSION "0.0-2"
    #define UNDEFINE 092873780
    #define GETDIR getCurrentDir()

#endif