#ifndef TP3_SERVER_BOARDEXCEPTION_H
#define TP3_SERVER_BOARDEXCEPTION_H
#include <exception>
#include "../common_src/Macros.h"

class BoardException : public std::exception {
private:
    char error[ERR_LEN];
public:
    explicit BoardException(const char* fmt, ...) noexcept;
    const char *what() const noexcept override;
    ~BoardException() noexcept;

    BoardException(const BoardException& other) = delete;
    BoardException& operator=(const BoardException& other) = delete;

    BoardException(BoardException&& other) noexcept;
    BoardException& operator=(BoardException&& other) noexcept;
};


#endif //TP3_SERVER_BOARDEXCEPTION_H
