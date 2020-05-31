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
            remove();
            clients.push_back(new ServerProxy(std::move(skt), std::ref(game), number));
            clients[i]->start();
            i++;
            //std::cout << "Aca en acceptor";
        }catch(const std::exception& e){
            game.stadistics();
            return;
        }
    }
}

void Acceptor::stop(){
    socket.socket_shutdown(SHUT_RDWR);
}

void Acceptor::remove(){
    std::vector<ServerProxy*> _clients;
    std::vector<ServerProxy*> ::iterator it = clients.begin();
    for (; it != clients.end(); ++it){
        if ((*it)->is_winner()){
            (*it)->join();
            delete (*it);
        } else{
            _clients.push_back((*it));
        }
    }
    clients.swap(_clients);
}