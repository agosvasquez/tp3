#ifndef CLIENT_COMMAND
#define CLIENT_COMMAND
#include <string>
#include "common_error.h"
class Protocol;
class Socket;


class ClientCommand{
protected:
    std::string& id;
    static bool is_number(std::string& line);
public:
    explicit ClientCommand(std::string& id);
    virtual~ClientCommand();
    virtual void execute(Protocol& p, Socket& s)=0;
    static  ClientCommand * get_command(std::string& line);
};

#endif
