#ifndef CLIENT_PROXY
#define CLIENT_PROXY
#include <string>
#include "common_socket.h"
#include "common_protocol.h"
#include <vector>

class ClientExeption : public std::exception {
public:
   const char *what() const throw() {
      return "Comunication fail!\n";
   }
};


class ClientProxy{
private:
    Socket socket;
    Protocol protocol;
    std::string response;
    char data_sen[5];

public:
    ClientProxy();
    ~ClientProxy();
    void send_command(char* data, int size);
    void recive_answer();
    void connect(char* host, char* service);
    void run(std::string& line);
};


#endif
