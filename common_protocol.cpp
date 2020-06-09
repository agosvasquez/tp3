#include "common_protocol.h"
#include <string.h>
#include <iostream>
#include <vector>

Protocol::Protocol(){}

Protocol::~Protocol(){}

void Protocol::send(Socket& s, std::string& buff){
    int size = buff.size();
    s.socket_send((char*)buff.c_str(), size);
}

void Protocol::send_number(Socket& s, std::string& buff){
    std::string final;
    short number = (short) std::stoi(buff);
    short transformed = htons(number);
    memcpy((char*)final.c_str(),&transformed, sizeof(uint16_t));
    s.socket_send((char*)final.c_str(), sizeof(uint16_t));
}

void Protocol::send_size(Socket& s, std::string& buff){
    char final[5];
    uint32_t* aux = (uint32_t*) buff.c_str();
    uint32_t transformed = htonl(*aux);
    memcpy(final,&transformed, sizeof(uint32_t));
    s.socket_send(final, sizeof(uint32_t));
}

void Protocol::receive(Socket& s, std::string& response, int size){
    std::vector<char> res(size+1,0);
    s.socket_receive(res.data(), size);
    response += res.data();
}

void Protocol::receive_number(Socket& s, std::string& response, int size){
    uint16_t number;
    s.socket_receive((char*)&number, size);
    uint16_t transformed = ntohs(number);
    response += std::to_string(transformed);
}

void Protocol::receive_size(Socket& s, std::string& response, int size){
    uint32_t len;
    s.socket_receive((char*)&len, size);
    uint32_t transformed = ntohl(len);
    response += std::to_string(transformed);
}
