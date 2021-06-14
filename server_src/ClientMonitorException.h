#ifndef TP3_CLIENTMONITOREXCEPTION_H
#define TP3_CLIENTMONITOREXCEPTION_H

#include <exception>
#include "../common_src/Macros.h"

class ClientMonitorException : public std::exception{
private:
    char error[ERR_LEN];
public:
    explicit ClientMonitorException(const char* fmt, ...) noexcept;
    const char *what() const noexcept override;
    ~ClientMonitorException() noexcept override;

    ClientMonitorException(const ClientMonitorException& other) = delete;
    ClientMonitorException& operator=
            (const ClientMonitorException& other) = delete;

    ClientMonitorException(ClientMonitorException&& other) noexcept;
    ClientMonitorException& operator=(ClientMonitorException&& other) noexcept;
};


#endif
