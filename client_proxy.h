#ifndef CLIENT_PROXY
#define CLIENT_PROXY
#include <string>
#include "common_socket.h"
#include "client_encode.h"
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
    ClientEncode encode;
    char data_rec[256];
    char data_sen[5];

public:
    ClientProxy();
    ~ClientProxy();
    void send_command(char* data, int size);
    char* recive_answer();
    void connect(char* host, char* service);
    void run(std::string line);
};


#endif
