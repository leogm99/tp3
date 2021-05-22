//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_CLIENT_PROTOCOL_H
#define TP3_CLIENT_PROTOCOL_H


#include <vector>
#include <map>
#include "common_Socket.h"

class CliProtocol {
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
    CliProtocol();
    int send(Socket& socket, const std::vector<unsigned char>& message);
    std::vector<unsigned char> receive(Socket& socket);

    ~CliProtocol();
};


#endif //TP3_CLIENT_PROTOCOL_H