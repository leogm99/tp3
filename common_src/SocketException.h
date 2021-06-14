#ifndef TP3_SOCKETEXCEPTION_H
#define TP3_SOCKETEXCEPTION_H

#include <exception>
#include "Macros.h"

class SocketException : public std::exception {
private:
    char error[ERR_LEN];
public:
    explicit SocketException(const char* fmt, ...) noexcept;
    const char *what() const noexcept override;
    ~SocketException() noexcept override;

    SocketException(const SocketException& other) = delete;
    SocketException& operator=(const SocketException& other) = delete;

    SocketException(SocketException&& other) noexcept;
    SocketException& operator=(SocketException&& other) noexcept;
};


#endif //TP3_SOCKETEXCEPTION_H
