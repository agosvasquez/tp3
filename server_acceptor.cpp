#include "server_acceptor.h"
#include <functional>
#include <iostream>
#include <exception>
#include <string>
#include <utility>

Acceptor::Acceptor(char* s, std::string file): service(s), admin(file){}

Acceptor::~Acceptor(){
    for (int i=0; i < (int)clients.size(); i++){
        clients[i]->join();
        delete clients[i];
    }
    stadistics();
}

void Acceptor::run(){
    socket.socket_bind_and_listen(service);
    while (1){
       std::string number = admin.get_secret_number();
        try{
            Socket skt = socket.socket_accept();
            remove();
            clients.push_back(new ServerProxy(std::move(skt),
             number, std::ref(stadistics)));
            clients[clients.size()-1]->start();
            //std::cout << "Aca en acceptor";
        }catch(const std::exception& e){
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
        if ((*it)->is_winner()| (*it)->is_loser()){
            (*it)->join();
            delete (*it);
        } else{
            _clients.push_back((*it));
        }
    }
    clients.swap(_clients);
}
