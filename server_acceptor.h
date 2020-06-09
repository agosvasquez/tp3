#ifndef SERVER_ACCEPTOR_H
#define SERVER_ACCEPTOR_H
#include "server_proxy.h"
#include "common_thread.h"
#include <atomic>
#include <vector>
#include <string>
#include "server_number_admin.h"
#include "server_stadistics_handler.h"

class Acceptor: public Thread{
private:
    Socket socket;
    char* service;
    std::vector<ServerProxy*> clients;
    NumbersAdmin admin;
    StadisticsHandler stadistics;
public:
    Acceptor(char* service, std::string file);
    ~Acceptor();
    void run();
    void stop();
    void remove();
};

#endif
