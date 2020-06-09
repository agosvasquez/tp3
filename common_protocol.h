#ifndef PROTOCOL
#define PROTOCOL
#include "common_socket.h"
#include <string>

class Protocol{
public:
    Protocol();
    ~Protocol();
    void send(Socket& s, std::string& buf);
    void send_number(Socket& s, std::string& buf);
    void send_size(Socket& s, std::string& buf);
    void receive(Socket&s, std::string& response, int size);
    void receive_number(Socket&s, std::string& response, int size);
    void receive_size(Socket&s, std::string& response, int size);
};

#endif
