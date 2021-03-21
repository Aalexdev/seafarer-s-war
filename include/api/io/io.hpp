#ifndef __IO__
#define __IO__

    #include <iostream>
    #include <cstring>
    #include <vector>
    using namespace std;

    /**
     * @brief return the content if a directory
     * 
     * @param directory_path the path of the directory
     * @return return content into a string vector
     */
    vector<string> directory_contents(string directory_path);

#endif