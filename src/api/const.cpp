#include "api/const.hpp"
#include <wtypes.h>
#include <windows.h>
#include <string>
#include <limits.h>

string getAppData(void){
    return getenv("APPDATA");
}

void GetDesktopResolution(int& horizontal, int& vertical){
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);

   horizontal = desktop.right;
   vertical = desktop.bottom;
}

string getCurrentDir(void){
    char buff[MAX_PATH];
    GetModuleFileName( NULL, buff, MAX_PATH );
    string::size_type position = string( buff ).find_last_of( "\\/" );
    return string( buff ).substr( 0, position);
}

string getMainDir(void){
    string buff = getCurrentDir();
    std::size_t pos = buff.find("bin");

    buff = buff.erase(pos);

    return buff;
}