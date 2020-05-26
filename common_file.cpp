#include "common_file.h"
#include <string>
#include <iostream>

File::File(std::string name): file(name){
    if (!file){
        //CAMBIAR
        std::cout << "File couldn be open!" << std::endl; 
        exit(1);  
    }
}

File::~File() {
    file.close();    
}

bool File::read(std::string& line){
    if (file >> line) return true;
    return false;
}

bool File::read(char& c){
    if (file >> c)return true;
    return false;
}

void File::go_first(){
    file.clear();
    file.seekg(0);
}