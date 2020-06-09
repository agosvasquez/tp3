#include "server_number_admin.h"
#include <string>
#include <utility>

NumbersAdmin::NumbersAdmin(std::string file_name):pos(0){
    std::fstream file(file_name);
    std::string line;
    while (file >> line){
        numbers.push_back(line);
    }
}

NumbersAdmin::~NumbersAdmin(){}

std::string NumbersAdmin::get_secret_number(){
    std::string numb = numbers[pos];
    pos +=1;
    //comparo contra size porque ya incremente 1
    if (pos == numbers.size())pos = 0;
    return std::move(numb);
}
