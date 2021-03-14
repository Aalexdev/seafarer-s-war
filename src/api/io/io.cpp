#include "api/io/io.hpp"

#include <dirent.h>

vector<string> directory_contents(string directory_path){
    DIR *dh;
    struct dirent * contents;
    vector<string> content;

    dh = opendir(directory_path.c_str());

    if (!dh){
        cout << "The given directory is not found";
        return content;
    }


    while ((contents = readdir(dh)) != NULL){
        string name = contents->d_name;
        content.push_back(name);
    }
    closedir ( dh );
    return content;
}