#include "server_helper.h"
#include <string>
#include <string.h>
#include <algorithm>
#include <functional>
#include <iostream>

namespace{
    std::string AYUDA = "Comandos válidos:​ \n\t​ AYUDA: despliega la lista de" 
    "comandos válidos​ \n\t​ RENDIRSE: pierde el juego automáticamente​ \n\t​ XXX: Número" 
    "de 3 cifras a ser enviado al servidor para adivinar el número secreto";
    std::string S = "Perdiste";
    std::string G = "Ganaste";
    std::string R = " regular";
    std::string B = " bien";
    std::string M = " mal";
    std::string INV = "Numero invalido. Debe ser de 3 cifras no repetidas";

}

ServerHelper::ServerHelper(Game& game): game(game){}

ServerHelper::~ServerHelper(){}

std::tuple<int,char*>  ServerHelper::decode_command(char command,short rec, int my_number){
    int good=0,reg=0;
    uint32_t size =0;
    digits.clear();
    static char s[256];
    memset(s,0,256);
    std::tuple<int,char*> tuple(0,0);
    if(command == 'h'){
        size = AYUDA.size();
        memcpy(s,(char*)&size, sizeof(uint32_t));
        memcpy(s+4, AYUDA.c_str(), size);
    }else if(command == 's'){
        size = S.size();
        memcpy(s,(char*)&size, sizeof(int));
        memcpy(s+4, S.c_str(), size);
    }else{
        int number = rec;
        if(!split_in_digits(number)) {
            size = INV.size();
            memcpy(s,(char*)&size, sizeof(int));
            memcpy(s+4, INV.c_str(), size);
            std::get<0>(tuple) = size+4+1;
            std::get<1>(tuple) = s;
            return tuple;
        }
        //std::cout <<"dig" << digits[0] << digits[1] << digits[2];
        good = game.check_good_d(number, my_number);
        int rr = game.check_regular_d(std::ref(digits), my_number);
        reg = rr-good;
        std::string g = std::to_string(good);
        std::string r = std::to_string(reg);
        std::string f;

        if (good > 0 && reg > 0){
           f = g +B+","+r + R;
        } else if(reg > 0){
            f= r + R;
        }else if(good == 3) f = G;
        else if (good > 0){
           f = g + B;
        }else{
            f = std::to_string(3)+ M;
        }
        size = f.size();
        std::cout << "len a guardar " << size << std::endl;
        memcpy(s,(char*)&size, sizeof(int));
        memcpy(s+4, f.c_str(), size);
    }
    memcpy(s+size+4,"\0", sizeof(char));
    std::get<0>(tuple) = size+4+1;
    std::get<1>(tuple) = s;
    std::cout <<"Tuple len"<< std::get<0>(tuple);
    return tuple;
}

bool ServerHelper::split_in_digits(int number){
    int n1 = number%10;
    number /= 10;
    int n2 = number%10;
    number /= 10;
    int n3 = number%10;

    std::cout<<"verify" << n1 << n2 << n3;
    digits.push_back(n3);
    if(verify_digit(n2))digits.push_back(n2);
    else return false;
    if(verify_digit(n1))digits.push_back(n1);
    else return false;
    return true;
}

bool ServerHelper::verify_digit(int d){
    if (std::find(digits.begin(), digits.end(), d) == digits.end())
        return true;
    return false;
}
