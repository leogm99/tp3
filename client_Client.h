//
// Created by leogm99 on 25/5/21.
//

#ifndef TP3_CLIENT_CLIENT_H
#define TP3_CLIENT_CLIENT_H
#include "client_Protocol.h"
#include "client_Command.h"

class Client {
private:
    CliProtocol clientProtocol;
    Command clientCommand;
    const size_t boardSize = 128;
    static const std::string msgWon;
    static const std::string msgLost;
    static const std::string msgTie;

public:
    Client(const char* host, const char* service);

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    int start();

    bool isGameDone(const std::string& messageReceived);

    ~Client();
};


#endif //TP3_CLIENT_CLIENT_H
