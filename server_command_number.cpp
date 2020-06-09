#include "server_command_number.h"
#include <functional>
#include <string>
#include <utility>
#include "iostream"
#include "common_socket.h"
#include "common_protocol.h"
#include "server_game.h"
#include <algorithm>
#include <string.h>

namespace{
    std::string LOSE = "Perdiste";
    std::string WIN = "Ganaste";
    std::string REG = " regular";
    std::string GOOD = " bien";
    std::string BAD = " mal";
    std::string INV = "Número inválido. Debe ser de 3 cifras no repetidas";
}

ServerCommandNumber::ServerCommandNumber(std::string& number,Game& game): 
ServerCommand(game), number(number){}

ServerCommandNumber::~ServerCommandNumber(){}

void ServerCommandNumber::execute(Protocol& p, Socket& s){
    std::string n, response;
    p.receive_number(s,n,2);
    int numb = std::stoi(n);
    if ((numb<100) | (numb > 999) | !is_valid(n)){
        response +=INV;
        answer(p,s,response);
        return;
    }
    response = number_response(std::ref(n));
    answer(p,s,response);
}

bool ServerCommandNumber::is_valid(std::string number){
    std::sort(number.begin(), number.end());
    return std::unique(number.begin(), number.end()) == number.end();
}

std::string ServerCommandNumber::number_response(std::string& n){
    std::string response;
    int good = game.check_good(n);
    int reg = game.check_regular(n) - good;
    std::string g = std::to_string(good);
    std::string r = std::to_string(reg);

    if (good == 3){response+= WIN; game.win_game();}
    else if (game.has_intents() == 0) response+= LOSE;
    else if (good > 0 && reg > 0)response+= g +GOOD+", "+r + REG;
    else if (reg > 0) response+= r + REG;
    else if (good > 0)response+= g + GOOD;
    else
        response+= std::to_string(3)+ BAD;
    return std::move(response);
}
