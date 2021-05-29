//
// Created by leogm99 on 19/5/21.
//

#include "common_Socket.h"
#include <cstring>
#include <iostream>

Socket::Socket(){
}

Socket::Socket(int fd) {
    this->fd = fd;
}

struct addrinfo *Socket::getAddrInfo(const char *host, const char *service, int caller_flags) {
    struct addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = caller_flags;

    struct addrinfo *results;
    int addrinfo = getaddrinfo(host, service, &hints, &results);
    if (addrinfo != 0){
        // alguna excepcion? no devuelvo nullptr
        return nullptr;
    }
    return results;
}

int Socket::bindAndListen(const char *service) {
    struct addrinfo * results;
    results = getAddrInfo(nullptr, service, AI_PASSIVE); // server

    if (!results){
        return -1;
    }

    struct addrinfo * aux = results;
    int bind_error = 0;
    for (; aux && !bind_error; aux = aux->ai_next){
        fd = socket(aux->ai_family,
                    aux->ai_socktype,
                    aux->ai_protocol);
        // si el fd es invalido, rip
        if (fd == -1){
            freeaddrinfo(results);
            return -1;
        }
        if ((bind_error = bind(fd, aux->ai_addr, aux->ai_addrlen)) == 0){
            break;
        }
        // falla bind, cierro el fd
        close(fd);
    }

    freeaddrinfo(results);
    if (bind_error || (fd < 0)){
        return -1;
    }

    if (listen(fd, 10) == -1){
        return -1;
    }

    return 0;
}

Socket Socket::accept() {
    int peerFd = ::accept(fd, nullptr, nullptr);
    if (errno == EINVAL){
        // ya se cerro y se hizo close
        fd = -1;
        throw std::invalid_argument("Listener closed");
    }
    return Socket(peerFd);
}

int Socket::connect(const char *host, const char *service) {
    struct addrinfo* results;
    results = getAddrInfo(host, service, 0);
    if (!results){
        return -1;
    }

    struct addrinfo *aux = results;
    int connect_error = 0;
    for (; aux; aux = aux->ai_next){
        fd = socket(aux->ai_family,
                          aux->ai_socktype,
                          aux->ai_protocol);
        if (fd == -1){
            freeaddrinfo(results);
            return -1;
        }

        connect_error = ::connect(fd, aux->ai_addr, aux->ai_addrlen);
        if (!connect_error){
            freeaddrinfo(results);
            return 0;
        }

        close(fd);
    }

    freeaddrinfo(results);
    return -1;
}

void Socket::shutdown() {
    if (fd > 0) {
        ::shutdown(fd, SHUT_RDWR);
        close(fd);
        fd = -1;
    }
}

ssize_t Socket::send(const void *buffer, size_t length) {
    ssize_t bytes_send = 0;
    const char *aux = static_cast<const char *>(buffer);

    while ((size_t) bytes_send < length){
        ssize_t send_ret = ::send(fd, &aux[bytes_send],
                                length - bytes_send, MSG_NOSIGNAL);
        if (send_ret == -1){
            break;
        }
        bytes_send += send_ret;
    }

    return bytes_send;
}

ssize_t Socket::receive(void *buffer, size_t length) {
    ssize_t bytes_recv = 0;
    char *aux = static_cast<char *>(buffer);

    while ((size_t) bytes_recv < length){
        ssize_t recv_ret = recv(fd, &aux[bytes_recv],
                                length - bytes_recv, 0);
        if (recv_ret == -1 || recv_ret == 0){
            break;
        }
        bytes_recv += recv_ret;
    }
    return bytes_recv;
}

Socket::~Socket() {
    if (fd > 0){
        ::shutdown(fd, SHUT_RDWR);
        close(fd);
    }
}

Socket::Socket(Socket &&other) noexcept
: fd(other.fd){
    other.fd = -1;
}

Socket &Socket::operator=(Socket &&other) noexcept{
    if (this == &other){
        return *this;
    }
    this->fd = other.fd;
    other.fd = -1;
    return *this;
}



