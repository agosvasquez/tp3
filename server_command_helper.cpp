#include "server_command_helper.h"
#include <functional>
#include "common_protocol.h"
#include "common_socket.h"
#include "server_game.h"
#include <string.h>
#include <string>

namespace{
    std::string H = "h";
    std::string AYUDA ="Comandos válidos:\n\tAYUDA: despliega la lista de "
    "comandos válidos\n\tRENDIRSE: pierde el "
    "juego automáticamente\n\tXXX: Número "
    "de 3 cifras a ser enviado al servidor para adivinar el número secreto"; 
}

ServerCommandHelper::ServerCommandHelper(Game& game): ServerCommand(game){}

ServerCommandHelper::~ServerCommandHelper(){}

void ServerCommandHelper::execute(Protocol& p, Socket& s){
    answer(p,s,AYUDA);
}
