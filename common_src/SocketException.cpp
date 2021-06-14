#include "SocketException.h"
#include <cstdarg>
#include <cstdio>

SocketException::SocketException(const char *fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(error, ERR_LEN, fmt, args);
    va_end(args);

    error[ERR_LEN - 1] = 0;
}

const char *SocketException::what() const noexcept {
    return error;
}

SocketException::~SocketException() noexcept {
}

SocketException::SocketException(SocketException &&other) noexcept {
    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
}

SocketException &SocketException::operator=(SocketException &&other) noexcept {
    if (this == &other){
        return *this;
    }

    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
    return *this;
}
