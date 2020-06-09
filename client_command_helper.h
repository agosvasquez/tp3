#ifndef CLIENT_COMMAND_HELPER
#define CLIENT_COMMAND_HELPER
#include "client_command.h"
#include <string>
class Protocol;
class Socket;

class ClientCommandHelper: public ClientCommand {
public:
    ClientCommandHelper();
    ~ClientCommandHelper();
    void execute(Protocol& p, Socket& s);
};

#endif

