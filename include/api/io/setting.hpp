#ifndef __SETTING__
#define __SETTING__

    #include "main.hpp"
    #include "api/functions/color.hpp"

    /**
     * @brief read a XML file
     * 
     * @param path the path of the file
     * @return retunr true on succes, false on error 
     */
    bool readXML(string path);

    /**
     * @brief get every files to load 
     * 
     * @param path the starting file
     * @return return files to load
     */
    int filesToLoad(string path);
        
    bool readXML_loading(string path);
    bool read(string path);

#endif