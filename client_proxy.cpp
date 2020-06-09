#include "client_proxy.h"
#include <iostream>
#include <string.h>
#include <vector>
#include<tuple>
#include "client_command.h"

namespace{
   int SIZE_STRING = 4;  
}

ClientProxy::ClientProxy(){}

ClientProxy::~ClientProxy(){}

void ClientProxy::run(std::string& line){
    try{
        ClientCommand *cmd = ClientCommand::get_command(line); 
        cmd->execute(protocol , socket);
        delete cmd;
        recive_answer();
        std::cout << response << std::endl;
    }catch(InvalidCommand& e){
        printf("%s", e.what());
        return;
    }
}


void ClientProxy::recive_answer(){
    std::string string_size;
    response.clear();
    //getting size
    protocol.receive_size(socket,string_size, SIZE_STRING);
    int size = std::stoi(string_size);
    protocol.receive(socket, response, size);
}

void ClientProxy::connect(char*host, char* service){
    socket.socket_connect(host, service);
}

