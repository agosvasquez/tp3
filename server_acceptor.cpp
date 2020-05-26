#include "server_acceptor.h"
#include <functional>
#include <iostream>
#include <exception>

Acceptor::Acceptor(char* s, std::string file): 
game(file), service(s), is_running(true){}

Acceptor::~Acceptor(){
    for (int i=0; i < (int)clients.size(); i++){
        clients[i]->join();
        delete clients[i];
    }
}

void Acceptor::run(){
    int i=0;
    if (socket.socket_bind_and_listen(service)<0) return;
    while(1){
        int number = game.get_secret_number();
        try{
            Socket skt = socket.socket_accept();
            //chequear si puedo liberar clientes
            clients.push_back(new ServerProxy(std::move(skt), std::ref(game), number));
            clients[i]->start();
            i++;
            std::cout << "Aca en acceptor";
        }catch(const std::exception& e){
            std::cout << "Finiish"<< std::endl; 
            return;
        }
    }
}

void Acceptor::stop(){
    socket.socket_shutdown(SHUT_RDWR);
}