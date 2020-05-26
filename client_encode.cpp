#include "client_encode.h"
#include <string>
#include "iostream"
#include <string.h>
#include <tuple>
namespace{
    std::string H = "AYUDA";
    std::string S = "RENDIRSE";
    char h = 'h';
    char s = 's';
    char n = 'n';
}

ClientEncode::ClientEncode(){}

ClientEncode::~ClientEncode(){}

 std::tuple<int,char*> ClientEncode::get_command_encoded(std::string line){
    static char buff[5];
    char c= '\0';
    std::tuple<int,char*> tuple(0,0);
    if(line == H){
        memcpy(buff,&h, sizeof(h));
        memcpy(buff+1,&c, sizeof(char));
        std::get<0>(tuple) = 1;
    }else if (line == S){
        memcpy(buff,&s, sizeof(char));
        memcpy(buff+1,&c, sizeof(char));
        std::get<0>(tuple) = 1;
    }else if (is_number(line)){
        
        memcpy(buff,&n, sizeof(char));
        short number = (short) std::stoi(line);
        
        memcpy(buff+1,(char*)&number, sizeof(short));
        memcpy(buff+3,&c, sizeof(char));
        std::get<0>(tuple) = 3;
        //std::cout << "strlen!!! " <<  strlen(buff) << std::endl; 
    }else{
        std::cout << "Error: comando inválido.";
        std::cout << "Escriba AYUDA para obtener ayuda"<< std::endl;
        return tuple;
    }
    std::get<1>(tuple) = buff;
    return tuple;
}

bool ClientEncode::is_number(std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
