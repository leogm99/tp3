//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_CLIENT_PROTOCOL_H
#define TP3_CLIENT_PROTOCOL_H


#include <vector>
#include <map>
#include "../common_src/Socket.h"

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

    Socket clientSocket;
public:
    CliProtocol(const char* host, const char* service);
    int send(const std::vector<unsigned char>& message);
    std::vector<unsigned char> receive();

    ~CliProtocol();
};


#endif //TP3_CLIENT_PROTOCOL_H
