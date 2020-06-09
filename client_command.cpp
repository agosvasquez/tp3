#include "client_command.h"
#include "client_command_helper.h"
#include "client_command_surrender.h"
#include "client_command_number.h"
#include "iostream"
#include "common_error.h"
#include "common_protocol.h"
#include "string.h"
#include <functional>

namespace{
    std::string AYUDA = "AYUDA";
    std::string RENDIRSE = "RENDIRSE";
}

ClientCommand::ClientCommand(std::string& id):id(id){}

ClientCommand::~ClientCommand(){}

ClientCommand* ClientCommand::get_command(std::string& line){
   ClientCommand* cmd;
   if (line == AYUDA) {
      cmd = new ClientCommandHelper();
   } else if (line == RENDIRSE) {
      cmd = new ClientCommandSurrender();
   } else if (is_number(line)) {
      cmd = new ClientCommandNumber(line);
   } else { 
        throw InvalidCommand();
   }
   return cmd;
}

bool ClientCommand::is_number(std::string& s){
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
