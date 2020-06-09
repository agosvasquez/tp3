#include "server_command.h"
#include "server_command_helper.h"
#include "server_command_surrender.h"
#include "server_command_number.h"
#include "iostream"
#include "common_error.h"
#include "common_protocol.h"
#include "server_game.h"
#include "string.h"
#include <functional>

namespace{
    std::string N = "n";
    std::string H = "h";
    std::string S = "s";
}

ServerCommand::ServerCommand(Game& game):game(game){}

ServerCommand::~ServerCommand(){}


ServerCommand* ServerCommand::get_command(std::string& line, Game& game){
    ServerCommand* cmd;
   if (line == H) {
        cmd = new ServerCommandHelper(game);
   } else if (line == S) {
        cmd = new ServerCommandSurrender(game);
   }else{
       cmd = new ServerCommandNumber(line, game);
   }
    return cmd;
}

void ServerCommand::answer(Protocol& p, Socket& s, std::string& msj){
    std::string size;
    int aux = msj.size();
    memcpy((char*) size.c_str(),(char*)&aux, sizeof(uint32_t));
    p.send_size(s, std::ref(size));
    p.send(s, msj);
}
