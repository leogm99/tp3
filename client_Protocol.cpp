//
// Created by leogm99 on 21/5/21.
//

#include "client_Protocol.h"
#include <iostream>

CliProtocol::CliProtocol() {
    byteMap = std::move(createMap());
}

int CliProtocol::send(Socket &socket, const std::vector<unsigned char>& message) {
    unsigned char code = message.at(0); // command code
    unsigned char commandBytes = byteMap.at(code);
    if (socket.send(&code, 1) < 1){
        return -1;
    };
    if (!commandBytes)
        return 0;
    uint16_t length = 1;
    if (commandBytes == 2){
        length = message.at(1) << 8 | message.at(2);
        uint16_t servLength = htons(length);
        if (socket.send(&servLength, commandBytes) < commandBytes){
            return -1;
        }
        const unsigned char* data = message.data();
        data += 3; // el mensaje empieza a partir de 3 bytes de la base
        if (socket.send(data, length) < length){
            return -1;
        }
        return 0;
    }

    if (socket.send(&message.at(1), length) < length){
        return -1;
    }
    return 0;
}

std::vector<unsigned char> CliProtocol::receive(Socket &socket) {
    uint16_t messageLength = 0;
    if (socket.receive(&messageLength, 2) < 2){
        return std::vector<unsigned char>(0);
    };

    messageLength = htons(messageLength);
    std::vector<unsigned char> message(messageLength);
    if (socket.receive(message.data(), messageLength) < messageLength){
        return message;
    };
    return message;
}

CliProtocol::~CliProtocol() {
}

