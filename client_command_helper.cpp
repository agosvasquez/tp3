#include "client_command_helper.h"
#include <functional>
#include "common_protocol.h"
#include "common_socket.h"
#include <string.h>

namespace{
    std::string H = "h";
}


ClientCommandHelper::ClientCommandHelper(): ClientCommand(std::ref(H)){}

ClientCommandHelper::~ClientCommandHelper(){}

void ClientCommandHelper::execute(Protocol& p, Socket& s){
    p.send(s, id);
}

