//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_SERVER_PROTOCOL_H
#define TP3_SERVER_PROTOCOL_H

#include <string>
#include <vector>
#include <map>
#include "common_Socket.h"

class ServProtocol {
private:
    static std::map<unsigned char, unsigned int> createMap(){
        std::map<unsigned char,
                unsigned int> mapping;
        mapping[0x6e] = 2;
        mapping[0x6c] = 0;
        mapping[0x6a] = 2;
        mapping[0x70] = 1;
        return mapping;
    }

    // byteMap that represents
    // how many bytes proceed to the
    // corresponding message to send/receive
    std::map<unsigned char, unsigned int> byteMap;
public:
    ServProtocol();

    ServProtocol(const ServProtocol& other) = delete;
    ServProtocol& operator=(const ServProtocol& other) = delete;

    ServProtocol(ServProtocol&& other) noexcept;
    ServProtocol& operator=(ServProtocol&& other) noexcept;

    int send(Socket& socket, const std::string& message);
    std::vector<unsigned char> receive(Socket& socket);

    ~ServProtocol();
};


#endif //TP3_SERVER_PROTOCOL_H
