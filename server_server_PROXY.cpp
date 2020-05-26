#include "server_server_PROXY.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <string.h>

ServerProxy::ServerProxy(Socket s,Game& game, int number):
socket(std::move(s)),my_number(number), helper(game),intents(10){
   
}

ServerProxy::~ServerProxy(){
}

void ServerProxy::run(){
    std::cout << "AcaAAAAAAA" << std::endl; 
    std::tuple<int,char*> tuple(0,0);
    while(has_intents()){
        try{
            std::cout << "AcaJIJI "<< std::endl;  
            short r = recive();
            tuple = helper.decode_command(command,r,my_number);
            std::cout << "s:afuera  " << std::get<1>(tuple)  << std::endl;
            std::cout << "s:afuera  " << std::get<0>(tuple)  << std::endl;
            send(std::get<1>(tuple), std::get<0>(tuple));
            std::cout << "short"<< r << std::endl;
            std::cout << "mynumb"<< my_number << std::endl;
            if((int)r == my_number){
                socket.socket_shutdown(SHUT_RDWR);
                return;
            }  
        }catch(const std::exception& e){
            return;
        }
    }
   
}
short ServerProxy::recive(){
    int size =2;
    short aux=0;
    if (socket.socket_receive(&command, 1)<=0) {throw SocketExeption();}
    if(command == 'n') {
        std::cout << "waitngg " << std::endl; 
        if (socket.socket_receive(data_rec, size)<=0) { throw SocketExeption();}
        std::cout << "recv: " << command <<std::endl;
        memcpy(&aux,data_rec,2);
        std::cout << "data_rec " << aux <<std::endl;
    }
    spend_intent();
    return aux;
}

void ServerProxy::send( char* s,size_t size){
    char aux[256];
    memcpy(aux,s,size);
    std::cout << "send: " << aux+4 <<std::endl;
    std::cout << "strlen!!" << size << std::endl;
    if (socket.socket_send(aux,size) <= 0){
        throw SocketExeption();
    }
}

void ServerProxy::spend_intent(){
    intents--;
}

bool ServerProxy::has_intents(){
    std::cout << intents << std::endl;
    return intents > 0;
}