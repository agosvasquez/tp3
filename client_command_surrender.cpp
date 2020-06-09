#include "client_command_surrender.h"
#include "common_protocol.h"
#include "common_socket.h"
#include <functional>
#include <string.h>
#include <string>

namespace{
    std::string S = "s";
}

ClientCommandSurrender::ClientCommandSurrender(): ClientCommand(S){}

ClientCommandSurrender::~ClientCommandSurrender(){}

void ClientCommandSurrender::execute(Protocol& p, Socket& s){
    p.send(s, id);
}
