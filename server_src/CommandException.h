#ifndef TP3_COMMANDEXCEPTION_H
#define TP3_COMMANDEXCEPTION_H


#include <exception>
#include "../common_src/Macros.h"

class CommandException : public std::exception{
private:
    char error[ERR_LEN];
public:
    explicit CommandException(const char* fmt, ...) noexcept;
    const char *what() const noexcept override;
    ~CommandException() noexcept override;

    CommandException(const CommandException& other) = delete;
    CommandException& operator=
            (const CommandException& other) = delete;

    CommandException(CommandException&& other) noexcept;
    CommandException& operator=(CommandException&& other) noexcept;
};


#endif
