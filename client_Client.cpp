#include <iostream>
#include <vector>
#include <string>
#include "client_Client.h"

const std::string Client::msgWon = "Felicitaciones! Ganaste!\n";
const std::string Client::msgLost = "Has perdido. Segui intentando!\n";
const std::string Client::msgTie = "La partida ha terminado en empate\n";

Client::Client(const char *host, const char *service)
: clientProtocol(host, service){
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
        std::vector<unsigned char> msg = std::move(clientProtocol.receive());
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

