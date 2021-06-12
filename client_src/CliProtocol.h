//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_CLIENT_PROTOCOL_H
#define TP3_CLIENT_PROTOCOL_H


#include "../common_src/Macros.h"
#include <vector>
#include <map>
#include "../common_src/Socket.h"

class CliProtocol {
private:
    static std::map<unsigned char, unsigned int> createMap(){
        std::map<unsigned char,
                unsigned int> mapping;
        mapping[CREAR] = 2;
        mapping[LISTAR] = 0;
        mapping[UNIRSE] = 2;
        mapping[JUGAR] = 1;
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

    CliProtocol(const CliProtocol& other) = delete;
    CliProtocol& operator=(const CliProtocol& other) = delete;

    CliProtocol(CliProtocol&& other) noexcept;
    CliProtocol& operator=(CliProtocol&& other) noexcept;

    ~CliProtocol();
};


#endif //TP3_CLIENT_PROTOCOL_H
