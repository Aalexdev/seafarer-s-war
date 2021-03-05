#ifndef __SAVE__
#define __SAVE__

    #include <iostream>
    #include <cstring>
    using namespace std;
    
    #include "api/io/xml.hpp"
    #include "ui/widgets/button.hpp"

    /**
     * @brief save game vars in the input file
     * 
     * @param path the destination path
     * @return * return true if save, false on error
     */
    bool saveXML(string path);

#endif