#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "../common_src/Macros.h"
#include "Client.h"

Client::Client(const char *host, const char *service)
: clientProtocol(host, service),
  msgWon(MSGWON),
  msgLost(MSGLOST),
  msgTie(MSGTIE){
}

int Client::start() {
    while (true){
        try {
            clientCommand.serializeCommand();
        } catch(const std::exception& e){
            continue;
        }
        if (clientProtocol.send(clientCommand.getCommand()) < 0){
            break;
        }
        std::vector<unsigned char> msg = clientProtocol.receive();
        if (msg.empty()){
            break;
        }
        std::string realMsg(msg.begin(), msg.end());
        std::cout << realMsg;
        if (isGameDone(realMsg)){
            break;
        }
    }
    return 0;
}

Client::~Client() {
}

bool Client::isGameDone(const std::string &messageReceived) {
    size_t msgLen = messageReceived.size();
    if ((boardSize + msgTie.size() == msgLen
        && messageReceived.find(msgTie) != std::string::npos)
        || ((boardSize + msgWon.size() == msgLen)
        && (messageReceived.find(msgWon) != std::string::npos))
        || ((boardSize + msgLost.size() == msgLen)
        && (messageReceived.find(msgLost) != std::string::npos))) {
        return true;
    }
    return false;
}

Client::Client(Client &&other) noexcept
: clientProtocol(std::move(other.clientProtocol)),
  clientCommand(std::move(other.clientCommand)){
}

Client &Client::operator=(Client &&other) noexcept {
    if (this == &other){
        return *this;
    }
    this->clientProtocol = std::move(other.clientProtocol);
    this->clientCommand = std::move(other.clientCommand);
    return *this;
}

