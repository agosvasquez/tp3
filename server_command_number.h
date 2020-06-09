#ifndef SERVER_COMMAND_NUMBER
#define SERVER_COMMAND_NUMBER
#include "server_command.h"
#include "common_error.h"
#include <string>
class Game;

class ServerCommandNumber: public ServerCommand{
private:
    std::string& number;
public:
    ServerCommandNumber(std::string& number,Game& game);
    ~ServerCommandNumber();
    void execute(Protocol& p, Socket& s);
    bool is_valid(std::string);
    std::string number_response(std::string& n);
};



#endif
