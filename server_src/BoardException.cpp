//
// Created by leogm99 on 19/5/21.
//

#include "BoardException.h"
#include <cstdio>
#include <cstdarg>

BoardException::BoardException(const char *fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(error, ERR_LEN, fmt, args);
    va_end(args);

    error[ERR_LEN - 1] = 0;
}

const char *BoardException::what() const noexcept {
    return error;
}

BoardException::~BoardException() noexcept {
}

BoardException::BoardException(BoardException &&other) noexcept {
    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
}

BoardException &BoardException::operator=(BoardException &&other) noexcept {
    if (this == &other){
        return *this;
    }

    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
    return *this;
}
