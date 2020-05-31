#ifndef COMMON_ACCEPTOR_H
#define COMMON_ACCEPTOR_H
#include "server_server_PROXY.h"
#include "common_thread.h"
#include <atomic>
#include <vector>

class Acceptor: public Thread{
private:
    Socket socket;
    Game game;
    char* service;
    std::atomic<bool> is_running;
    std::vector<ServerProxy*> clients;
public:
    Acceptor(char* service, std::string file);
    ~Acceptor();
    void run();
    void stop();
    void remove();
};

#endif
