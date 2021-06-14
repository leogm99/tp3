#include <cstdarg>
#include <cstdio>
#include "ClientMonitorException.h"

ClientMonitorException::ClientMonitorException(const char *fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(error, ERR_LEN, fmt, args);
    va_end(args);

    error[ERR_LEN - 1] = 0;
}

const char *ClientMonitorException::what() const noexcept {
    return error;
}

ClientMonitorException::~ClientMonitorException() noexcept {
}

ClientMonitorException::
ClientMonitorException(ClientMonitorException &&other) noexcept {
    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
}

ClientMonitorException
&ClientMonitorException::operator=
        (ClientMonitorException &&other) noexcept {
    if (this == &other){
        return *this;
    }

    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
    return *this;
}
