#ifndef COMMON_CLIENT_H
#define COMMON_CLIENT_H
#include "common_socket.h"
#include "client_proxy.h"

class Client{
private:
    ClientProxy client_proxy;
public:
    Client();
    ~Client();
    void run(char* host_name,  char* service, std::string line);
};

#endif 
