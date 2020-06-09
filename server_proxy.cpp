#include "server_proxy.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <string.h>
#include <string>
#include <utility>
#include "server_command.h"
#include "server_stadistics_handler.h"

ServerProxy::ServerProxy(Socket s, std::string number, StadisticsHandler& st):
socket(std::move(s)),winner(false), game(number),
 stadistics(st){}

ServerProxy::~ServerProxy(){}

void ServerProxy::run(){
    while (game.has_intents()){
        try{
            recive();
            ServerCommand* s_cmd = ServerCommand::get_command(cmd, game);
            s_cmd->execute(std::ref(protocol),std::ref(socket));
            delete s_cmd;
            if (game.is_winner()) {
                stadistics.increment_winners();
                socket.socket_shutdown(SHUT_RDWR);
                return;
            }
            if (game.is_loser()){
                stadistics.increment_losers();
                socket.socket_shutdown(SHUT_RDWR);
                return;
            }
        }catch(const std::exception& e){
            return;
        }
    }
    stadistics.increment_losers();
}

void ServerProxy::recive(){
    cmd.clear();
    game.spend_intent();
    protocol.receive(socket,cmd,1); 
}


bool ServerProxy::is_winner(){
    return game.is_winner();
}

bool ServerProxy::is_loser(){
    return game.is_loser();
}
