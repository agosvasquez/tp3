#include "client_proxy.h"
#include <iostream>
#include <string.h>
#include <vector>
#include<tuple>

namespace{
   int SIZE_STRING = 4;  
}

ClientProxy::ClientProxy(){}

ClientProxy::~ClientProxy(){
    socket.socket_shutdown(SHUT_RDWR);
}

void ClientProxy::run(std::string line){
    std::tuple<int,char*> data = encode.get_command_encoded(line);
    if(std::get<0>(data) == 0)return;
    send_command(std::get<1>(data), std::get<0>(data));
    char* answer =recive_answer();
    std::cout << answer <<std::endl;
}

void ClientProxy::send_command(char* data, int size){
    char aux[5];
    memcpy(aux,data,size);
    int bytes = socket.socket_send(aux, size);
    if (bytes <= 0) {
        throw ClientExeption();
    }
    std::cout << "strlen " <<  size << std::endl; 
    std::cout << "bytes " << bytes << std::endl;
}

char* ClientProxy::recive_answer(){
    uint32_t size=0;;
    memset(data_rec,0,256);
    //getting size
    if (socket.socket_receive((char*)&size, SIZE_STRING)<0) {
        throw ClientExeption();
    }
    
    std::cout << "size answer " << size << std::endl; 
    if (socket.socket_receive(data_rec, size+1)<0) {
        throw ClientExeption();
    }
    static char aux[256];
    memset(aux,0,256);
    memcpy(aux,data_rec,size);
    return aux;
}

void ClientProxy::connect(char*host, char* service){
    if(socket.socket_connect(host, service)<0){
        std::cout << "FALLO!!!";
        throw ClientExeption(); 
    } 
}

