#ifndef CLIENT_COMMAND_HELPER
#define CLIENT_COMMAND_HELPER
#include "server_command.h"
class Game;

class ServerCommandHelper: public ServerCommand {
public:
    explicit ServerCommandHelper(Game& game);
    ~ServerCommandHelper();
    void execute(Protocol& p, Socket& s);
};



#endif
