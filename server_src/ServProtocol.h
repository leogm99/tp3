#ifndef TP3_SERVER_PROTOCOL_H
#define TP3_SERVER_PROTOCOL_H

#include "../common_src/Macros.h"
#include <string>
#include <vector>
#include <map>
#include "../common_src/Socket.h"

class ServProtocol {
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
