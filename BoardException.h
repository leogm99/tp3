//
// Created by leogm99 on 19/5/21.
//

#ifndef TP3_BOARDEXCEPTION_H
#define TP3_BOARDEXCEPTION_H
#include <exception>
#define ERR_LEN 256

class BoardException : public std::exception {
private:
    char error[ERR_LEN];
public:
    explicit BoardException(const char* fmt, ...) noexcept;
    virtual const char *what() const noexcept;
    virtual ~BoardException() noexcept;
};


#endif //TP3_BOARDEXCEPTION_H
