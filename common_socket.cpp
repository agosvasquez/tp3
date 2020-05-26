#include "common_socket.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <exception>
#include <vector>

Socket::Socket():queue_len_listen(10), fd(-1){}

Socket::~Socket(){
    if(fd != -1)
        socket_shutdown(SHUT_RDWR);
}

Socket::Socket(int fd):fd(fd){}

Socket::Socket(Socket&& other) : fd(other.fd) {
    other.fd = -1;
}

Socket& Socket::operator=(Socket&& other){
    fd = other.fd;
    other.fd = -1;
    return *this;
}


void Socket::socket_settings(struct addrinfo& hints){
    hints.ai_family= AF_INET;
    hints.ai_socktype= SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol= 6;
}

void Socket::socket_shutdown(int channel){
    shutdown(fd, channel);
    close(fd);
    fd = -1;
}

int Socket::socket_bind_and_listen(const char* service){
    struct addrinfo hints, *res;
    int s, sfd=0;
    int opt =1;
    
    socket_settings(hints); 
    if ((s = getaddrinfo(NULL,service, &hints, &res)) != 0) {
         std::cout << "fallo gett";
        return -1;
    }
       
        //throw_sterr("getaddrinfo:", gai_strerror(s));
    
    if ((sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol))< 0){
        std::cout << "fallo crear socket";
        freeaddrinfo(res);
        return -1;
        //throw_error("create socket");
    }
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        std::cout << "fallo setsockop error";
        freeaddrinfo(res);
        return -1;
        //throw_error("setsockop error");
    }    
    if (bind(sfd, res->ai_addr, res->ai_addrlen) < 0){
        std::cout << "fallo bind";
        freeaddrinfo(res);
        return -1;
        //throw_error("Bind error");
    }
    if (listen(sfd, queue_len_listen) < 0){
        std::cout << "lisnte error";
        freeaddrinfo(res);
        return -1;
        //throw_error("Listen error");
    }
    
    freeaddrinfo(res);
    fd = sfd; 
    return 0;            
}

Socket Socket::socket_accept(){
    int s = accept(fd, NULL,NULL);
    if (s < 0) {
        //std::cout << "not accepted connection";
        //CAMBIAR NO OLVIDARSE SOLO LOCAL
        throw SocketExeption();//throw_error("Not accepted connection");
    }
    
    return std::move(Socket(s));
}

int Socket::socket_connect(const char* host_name, const char* service){
    struct addrinfo hints, *res, *r;
    int s, socket_fd;

    socket_settings(hints);

    if ((s = getaddrinfo(host_name, service, &hints,&res)) !=0) {
        std::cout << "fallo getaddr";
        return-1;
    }
        
        //throw_sterr("getaddr:", gai_strerror(s));
   r = res;
   for ( r = res; r != NULL; r = r->ai_next) {
        socket_fd = socket(r->ai_family, r->ai_socktype,r->ai_protocol);
        if (socket_fd == -1) continue;
        if (connect(socket_fd, r->ai_addr, r->ai_addrlen) != -1){
            fd = socket_fd;
            break;                  
        }
        close(socket_fd);
    }
    if (!r) {
        std::cout << "not connected";
        freeaddrinfo(res); 
        return -1;
        //throw_sterr("Could not connect\n", NULL);               
    }
    freeaddrinfo(res);  
    return 0;
}

int Socket::socket_send(char* buff , size_t length){
    size_t sum_b = 0;
    int bytes =0;
    int to_send= length;
    while (sum_b != length){
        if ((bytes = send(fd,buff+sum_b,to_send,MSG_NOSIGNAL))<0){
            std::cout << "fallo send";
            return -1;
        } 
            
            //throw_error("send failed");
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
        if ((bytes = recv(fd, buff+sum_b, to_read,0)) <0){
            std::cout << "fallo recv";
            return -1;
        } 

            //throw_error("recive failed");
        // client closed
        if (bytes == 0) return 0;
        sum_b += bytes;
        to_read -= bytes;
        std::cout << "receive " << to_read << std::endl;
    }
    memcpy(buff + length, "\0", 1);
    std::cout << "saliendo " << std::endl;
    std::cout << "buff " << buff << std::endl;
    return sum_b;
}
