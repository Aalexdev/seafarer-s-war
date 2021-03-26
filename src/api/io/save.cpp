#include "api/io/save.hpp"

#include <iostream>
#include <fstream>
using namespace std;

#include "main.hpp"

string path;

int saveXMLThread(void* ptr){

    fstream file;
    file.open(path, ios::out);

    if (!file){
        if (IS_ERR_OPEN) ERR << "ERRPR :: saveXML, cannot open '" << path << "' file" << endl;
        return false;
    }

    file << "<?xml version=\"0.1.0\" encoding=\"utf-8\"?>" << endl; 
    file << "<color r=\"" << WINDOW_R << "\" g=\"" << WINDOW_G << "\" b=\"" << WINDOW_B << "\" a=\"" << WINDOW_A << "\"/>" << endl;
    file << "<clearEntitys/>" << endl;
    file << endl;

    file << "<setPlayer type=\"" << PLAYER->getType()->get_name() << "\" x=\"" << PLAYER->getX() << "\" y=\"" << PLAYER->getY() << "\" height=\"" << PLAYER->getZ() << "\" angle=\"" << PLAYER->getAngle() << "\">" << endl;
    file << "\t<part health=\"" << PLAYER->getHealth() << "\"/>" << endl;
    file << "\t<equipments>" << endl;

    int l;
    Equipment** equi = PLAYER->getEquipments(&l);
    for (int i=0; i<l; i++){
        if (equi[i]){
            file << "\t\t<equipment name=\"" << equi[i]->getType()->getName() << "\" id=\"" << i << "\" angle=\"" << equi[i]->getAngle() << "\"/>" << endl;
        }
    }

    file << "\t</equipments>" << endl;
    file << "\t<events>" << endl;
    file << "\t\t<keypad>" << endl;

    file << "\t\t\t<key tag=\"" << SDL_GetScancodeName(PLAYER_CONTROL.engineUp) << "\" out=\"engineUp\"/>" << endl;
    file << "\t\t\t<key tag=\"" << SDL_GetScancodeName(PLAYER_CONTROL.engineDown) << "\" out=\"engineDown\"/>" << endl;
    file << "\t\t\t<key tag=\"" << SDL_GetScancodeName(PLAYER_CONTROL.turnLeft) << "\" out=\"turnLeft\"/>" << endl;
    file << "\t\t\t<key tag=\"" << SDL_GetScancodeName(PLAYER_CONTROL.turnRight) << "\" out=\"turnRight\"/>" << endl;
    file << "\t\t\t<key tag=\"" << SDL_GetScancodeName(PLAYER_CONTROL.layerDown) << "\" out=\"layerDown\"/>" << endl;
    file << "\t\t\t<key tag=\"" << SDL_GetScancodeName(PLAYER_CONTROL.layerUp) << "\" out=\"layerUp\"/>" << endl;

    file << "\t\t</keypad>" << endl; 
    file << "\t</events>" << endl;
    file << "</setPlayer>" << endl;

    file << endl;

    for (Entity* e : ENTITY){
        if (e){
            file << "<summonEntity type=\"" << e->getType()->get_name() << "\" x=\"" << e->getX() << "\" y=\"" << e->getY() << "\" height=\"" << e->getZ() << "\" angle=\"" << e->getAngle() << "\">" << endl;

            file << "\t<part health=\"" << e->getHealth() << "\"/>" << endl;
            file << "\t<equipments>" << endl;

            int l;
            Equipment** equi = e->getEquipments(&l);

            for (int i=0; i<l; i++){
                if (equi[i]){
                    file << "\t\t<equipment name=\"" << equi[i]->getType()->getName() << "\" id=\"" << i << "\" angle=\"" << equi[i]->getAngle() << "\"/>" << endl;
                }
            }

            file << "\t</equipments>" << endl;
            file << "</summonEntity>" << endl;
        }
        file << endl;
    }

    file.close();
    return true;
}

bool saveXML(string path_file){

    path = path_file;
    SDL_Thread* save = SDL_CreateThread(saveXMLThread, "save", (void*)NULL);

    return true;
}