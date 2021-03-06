#ifndef TP3_CLIENT_CLIENT_H
#define TP3_CLIENT_CLIENT_H
#include "CliProtocol.h"
#include "Command.h"
#include <string>

class Client {
private:
    CliProtocol clientProtocol;
    Command clientCommand;
    const size_t boardSize = 128;
    const std::string msgWon;
    const std::string msgLost;
    const std::string msgTie;

public:
    Client(const char* host, const char* service);

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    Client(Client&& other) noexcept;
    Client& operator=(Client&& other) noexcept;

    int start();

    bool isGameDone(const std::string& messageReceived);

    ~Client();
};


#endif //TP3_CLIENT_CLIENT_H
