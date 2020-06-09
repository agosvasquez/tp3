#ifndef SERVER_COMMAND_SURRENDER
#define SERVER_COMMAND_SURRENDER
#include "server_command.h"
#include <string>
class Game;

class ServerCommandSurrender: public ServerCommand{
public:
    explicit ServerCommandSurrender(Game& game);
    ~ServerCommandSurrender();
    void execute(Protocol& p, Socket& s);
};


#endif
