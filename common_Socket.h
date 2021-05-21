//
// Created by leogm99 on 19/5/21.
//

#ifndef TP3_COMMON_SOCKET_H
#define TP3_COMMON_SOCKET_H
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>

class Socket {
private:
    int fd;
    struct addrinfo* getAddrInfo(const char* host,
                                 const char* service,
                                 int caller_flags);
    explicit Socket(int fd);
public:
    Socket();

    Socket(const Socket& other) = delete;
    Socket& operator=(const Socket& other) = delete;

    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    int bindAndListen(const char* service);
    Socket accept();
    int connect(const char* host, const char* service);

    ssize_t send(const void* buffer, size_t length);
    ssize_t receive(void* buffer, size_t length);
    ~Socket();
};


#endif //TP3_COMMON_SOCKET_H
