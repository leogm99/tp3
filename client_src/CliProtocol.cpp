#include "CliProtocol.h"
#include <vector>
#include <iostream>
#include <utility>

CliProtocol::CliProtocol(const char* host, const char* service) :
byteMap(std::move(createMap())) {
    if (clientSocket.connect(host, service) < 0){
        throw std::invalid_argument("Connect failed, server is not up\n");
    }
}

int CliProtocol::send(const std::vector<unsigned char>& message) {
    unsigned char code = message.at(0); // command code
    unsigned char commandBytes = byteMap.at(code);
    if (clientSocket.send(&code, 1) < 1){
        return -1;
    }
    if (!commandBytes)
        return 0;
    uint16_t length = 1;
    if (commandBytes == 2){
        length = message.at(1) << 8 | message.at(2);
        uint16_t servLength = htons(length);
        if (clientSocket.send(&servLength, commandBytes) < commandBytes){
            return -1;
        }
        const unsigned char* data = message.data();
        data += 3; // el mensaje empieza a partir de 3 bytes de la base
        if (clientSocket.send(data, length) < length){
            return -1;
        }
        return 0;
    }

    if (clientSocket.send(&message.at(1), length) < length){
        return -1;
    }
    return 0;
}

std::vector<unsigned char> CliProtocol::receive() {
    uint16_t messageLength = 0;
    if (clientSocket.receive(&messageLength, 2) < 2){
        return std::vector<unsigned char>(0);
    }
    messageLength = htons(messageLength);
    std::vector<unsigned char> message(messageLength);
    if (clientSocket.receive(message.data(), messageLength) < messageLength){
        return message;
    }
    return message;
}

CliProtocol::~CliProtocol() {
}

