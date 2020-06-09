#include "server_command_surrender.h"
#include "common_protocol.h"
#include "common_socket.h"
#include <functional>
#include <string.h>
#include <string>
#include "server_game.h"

namespace{
    std::string LOSER = "Perdiste";
}

ServerCommandSurrender::ServerCommandSurrender(Game& game): 
ServerCommand(game){}

ServerCommandSurrender::~ServerCommandSurrender(){
}

void ServerCommandSurrender::execute(Protocol& p, Socket& s){
    game.loose_game();
    answer(p,s,LOSER);
}
