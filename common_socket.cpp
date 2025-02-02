#include "common_socket.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <utility>
#include <exception>
#include <vector>
#include <functional>
#include "common_error.h"

Socket::Socket():queue_len_listen(10), fd(-1){}

Socket::~Socket(){
    if (fd != -1)
        close(fd);
}
Socket::Socket(int fd):fd(fd){}

Socket::Socket(Socket&& other)noexcept : fd(other.fd) {
    other.fd = -1;
}

Socket& Socket::operator=(Socket&& other){
    fd = other.fd;
    other.fd = -1;
    return *this;
}


void Socket::socket_settings(struct addrinfo& hints){
    memset(&hints,0,sizeof(struct addrinfo));
    hints.ai_family= AF_INET;
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_flags = 0;
}

void Socket::socket_shutdown(int channel){
    shutdown(fd, channel);
}

int Socket::find_socket(struct addrinfo** res, int& sfd){
    struct addrinfo*r = *res;
    int socket_fd;
    for (; r != NULL; r = r->ai_next) {
        socket_fd = socket(r->ai_family, r->ai_socktype,r->ai_protocol);
        if (socket_fd == -1) continue;
        if (connect(socket_fd, r->ai_addr, r->ai_addrlen) != -1){
            sfd = socket_fd;
            break;                  
        }
        close(socket_fd);
    }
    if (!r) {
        freeaddrinfo(*res); 
        return -1;            
    }
    return 0;
}

int Socket::socket_bind_and_listen(const char* service){
    struct addrinfo hints, *res, *r;
    int s, sfd=0;
    int opt =1;
    socket_settings(std::ref(hints)); 
    if ((s = getaddrinfo(NULL,service, &hints, &res)) != 0) 
        throw Error("fallo gett");
    
    for (r=res ; r != NULL; r = r->ai_next) {
        sfd = socket(r->ai_family, r->ai_socktype,r->ai_protocol);
        if (sfd == -1) continue;
    }
    if (sfd == -1) throw Error("could not create socket");
    
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        freeaddrinfo(res);
        throw Error("setsockop error");
    }    
    
    if (bind(sfd, res->ai_addr, res->ai_addrlen) < 0){
        freeaddrinfo(res);
        throw Error("Bind error");
    }
    if (listen(sfd, queue_len_listen) < 0){
        freeaddrinfo(res);
        throw Error("Listen error");
    }
    freeaddrinfo(res);
    fd = sfd; 
    return 0;            
}

Socket Socket::socket_accept(){
    int s = accept(fd, NULL,NULL);
    if (s < 0) throw Error("Not accepted connection");
    return std::move(Socket(s));
}

int Socket::socket_connect(const char* host_name, const char* service){
    struct addrinfo hints, *res;
    int s, sfd;

    socket_settings(hints);

    if ((s = getaddrinfo(host_name, service, &hints,&res)) !=0){
        throw Error("fail getadd");
    } 
       
    if (find_socket(&res,std::ref(sfd)) < 0) {  
        throw Error("couldn connect");
    }
    fd = sfd;
    freeaddrinfo(res);  
    return 0;
}

int Socket::socket_send(char* buff , size_t length){
    size_t sum_b = 0;
    int bytes =0;
    int to_send= length;
    while (sum_b != length){
        if ((bytes = send(fd,buff+sum_b,to_send,MSG_NOSIGNAL))<0)    
            throw Error("send failed");
        sum_b += bytes;
        to_send -= bytes;
    }
    return sum_b;
}

int Socket::socket_receive(char* buff, size_t length){
    size_t sum_b = 0;
    int bytes = 0;
    int to_read = length;
    while (sum_b != length){
        if ((bytes = recv(fd, buff+sum_b, to_read,0)) <0)
            throw Error("recive failed");
        // client closed
        if (bytes == 0) return 0;
        sum_b += bytes;
        to_read -= bytes;  
    }
    memcpy(buff + length, "\0", 1);
    return sum_b;
}


