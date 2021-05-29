#include <utility>
#include <string>
#include <vector>
#include "server_Protocol.h"


ServProtocol::ServProtocol()
:byteMap(std::move(createMap())){
}

int ServProtocol::send(Socket &socket, const std::string &message) {
    uint16_t msgLen = message.size();
    uint16_t msgLenCli = ntohs(msgLen);
    if (socket.send(&msgLenCli, 2) < 2){
        return -1;
    }
    if (socket.send(message.c_str(), msgLen) < msgLen){
        return -1;
    }
    return 0;
}

std::vector<unsigned char> ServProtocol::receive(Socket &socket) {
    uint8_t code = 0;
    if (socket.receive(&code, 1) < 1){
        return std::vector<unsigned char>(0);
    }
    size_t bytesToRead = byteMap.at(code);

    std::vector<unsigned char> v;
    v.push_back(code);

    if (!bytesToRead){
        return v;
    }

    if (bytesToRead == 2){
        uint16_t msgLen = 0;
        if (socket.receive(&msgLen, 2) < 2){
            return std::vector<unsigned char>();
        }
        msgLen = ntohs(msgLen);
        v.resize(1 + 2 + msgLen);
        if (socket.receive(v.data() + 3, msgLen) < msgLen){
            return std::vector<unsigned char>();
        }
        return v;
    }

    v.resize(2);
    if (socket.receive(v.data() + 1, 1) < 1){
        return std::vector<unsigned char>();
    }
    return v;
}

ServProtocol::~ServProtocol() {
}

ServProtocol::ServProtocol(ServProtocol &&other) noexcept {
    this->byteMap = std::move(other.byteMap);
}

ServProtocol &ServProtocol::operator=(ServProtocol &&other) noexcept {
    this->byteMap = std::move(other.byteMap);
    return *this;
}
