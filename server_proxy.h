#ifndef SERVER_PROXY
#define SERVER_PROXY
#include "common_socket.h"
#include "common_thread.h"
#include "common_protocol.h"
#include "server_game.h"
#include <string>
class StadisticsHandler;

class ServerProxy: public Thread{
private:
    Socket socket;
    std::atomic<bool> winner;
    Game game;
    Protocol protocol;
    std::string cmd;   
    StadisticsHandler& stadistics;
public:
    ServerProxy(Socket s, std::string number, StadisticsHandler& stadistics);
    ~ServerProxy();
    void recive();
    void send(char* s,size_t size);
    void run();
    bool is_winner();
    bool is_loser();
};


#endif
