#include "client_command_number.h"
#include <functional>
#include "iostream"
#include "common_socket.h"
#include "common_protocol.h"
#include <string>

namespace{
    std::string N = "n";
    int MAX_NUMBER_ALLOWED= 65536;
}

ClientCommandNumber::ClientCommandNumber(std::string number):
 ClientCommand(std::ref(N)){
    if (number.size() > 5) throw InvalidCommand();
    int to_check = std::stoi(number);
    if (to_check > MAX_NUMBER_ALLOWED) throw InvalidCommand();
    this->number = number;
}

ClientCommandNumber::~ClientCommandNumber(){}

void ClientCommandNumber::execute(Protocol& p, Socket& s){
    p.send(s, id);
    p.send_number(s, number);
}
