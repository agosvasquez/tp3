#ifndef CLIENT_COMMAND_SURRENDER
#define CLIENT_COMMAND_SURRENDER
#include "client_command.h"
class Protocol;
class Socket;

class ClientCommandSurrender: public ClientCommand{
public:
    ClientCommandSurrender();
    ~ClientCommandSurrender();
    void execute(Protocol& p, Socket& s);
};


#endif
