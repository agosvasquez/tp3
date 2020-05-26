#ifndef SOCKET_H
#define SOCKET_H
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>


class SocketExeption : public std::exception {
public:
   const char *what() const throw() {
      return "Socket accept fail!\n";
   }
};


class Socket{
private:
    int queue_len_listen;
   
public:
    int fd;
    Socket();
    ~Socket();
    Socket(Socket&& other);
    Socket(int fd);
    Socket& operator=(Socket&& other);
    void socket_settings(struct addrinfo& hints);
    void socket_shutdown(int channel);
    int socket_bind_and_listen(const char* service);
    Socket socket_accept();
    int socket_connect(const char* host_name, const char* service);
    int socket_send(char* buff, size_t length);
    int socket_receive(char* buf, size_t length);
};


#endif 
