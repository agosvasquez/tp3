#ifndef CLIENT_COMMAND_NUMBER
#define CLIENT_COMMAND_NUMBER
#include "client_command.h"
#include "common_error.h"
#include <string>

class ClientCommandNumber: public ClientCommand{
private:
    std::string number;
public:
    explicit ClientCommandNumber(std::string number);
    ~ClientCommandNumber();
    void execute(Protocol& p, Socket& s);
};

#endif
