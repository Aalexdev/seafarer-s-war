#ifndef __CONST__
#define __CONST__

    #include "main.hpp"

    std::string getAppData(void);
    void GetDesktopResolution(int& horizontal, int& vertical);
    std::string getCurrentDir(void);
    std::string getMainDir(void);
    
    #define APPDATA getAppData()
    #define VERSION "0.0-1"
    #define UNDEFINE 092873780
    #define GETDIR getCurrentDir()

#endif