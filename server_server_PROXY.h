#ifndef SERVER_PROXY
#define SERVER_PROXY
#include "common_socket.h"
#include "common_game.h"
#include "common_thread.h"
#include "server_helper.h"


class ServerProxy: public Thread{
private:
    Socket socket;
    int my_number;
    ServerHelper helper;
    std::atomic<int> intents;
    std::atomic<bool> winner;
    char data_rec[256];
    char data_sen[256];
    char command;
    Game& game;
public:
    ServerProxy(Socket s,Game& game, int number);
    ~ServerProxy();
    short recive();
    void send( char* s,size_t size);
    void run();
    void spend_intent();
    bool has_intents();
    bool is_winner();
};


#endif
