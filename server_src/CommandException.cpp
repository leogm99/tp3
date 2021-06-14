#include "CommandException.h"
#include <cstdio>
#include <cstdarg>

CommandException::CommandException(const char *fmt, ...) noexcept {
    va_list args;
    va_start(args, fmt);
    vsnprintf(error, ERR_LEN, fmt, args);
    va_end(args);

    error[ERR_LEN - 1] = 0;
}

const char *CommandException::what() const noexcept {
    return error;
}

CommandException::~CommandException() noexcept {
}

CommandException::CommandException(CommandException &&other) noexcept {
    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
}

CommandException &CommandException::operator=(CommandException &&other) noexcept {
    if (this == &other){
        return *this;
    }
    for (size_t i = 0; i < ERR_LEN; ++i){
        error[i] = other.error[i];
    }
    return *this;
}
