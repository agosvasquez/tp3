#ifndef SERVER_COMMAND
#define SERVER_COMMAND
#include <string>
class Protocol;
class Socket;
class Game;

class ServerCommand{
protected:
    Game& game;
    static bool is_number(std::string& line);
public:
    explicit ServerCommand(Game& game);
    virtual ~ServerCommand();
    virtual void execute(Protocol& p, Socket& s){}
    void answer(Protocol& p, Socket& s,std::string& msj);
    static ServerCommand * get_command(std::string& line, Game& game);
};

#endif
