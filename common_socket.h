#ifndef SOCKET_H
#define SOCKET_H
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "common_error.h"


class Socket{
protected:
    int queue_len_listen;
    int find_socket(struct addrinfo** res, int& sfd);
    explicit Socket(int fd);
public:
    int fd;
    Socket();
    ~Socket();
    Socket(Socket&& other)noexcept;
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
