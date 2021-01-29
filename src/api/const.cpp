#include "api/const.hpp"
#include <wtypes.h>
#include <windows.h>
#include <string>
#include <limits.h>

std::string getAppData(void){
    return getenv("APPDATA");
}

void GetDesktopResolution(int& horizontal, int& vertical){
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);

   horizontal = desktop.right;
   vertical = desktop.bottom;
}

std::string getCurrentDir(void){
    char buff[MAX_PATH];
    GetModuleFileName( NULL, buff, MAX_PATH );
    string::size_type position = std::string( buff ).find_last_of( "\\/" );
    return std::string( buff ).substr( 0, position);
}

std::string getMainDir(void){
    std::string buff = getCurrentDir();
    std::size_t pos = buff.find("bin");

    buff = buff.erase(pos);

    return buff;
}