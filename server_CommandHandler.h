//
// Created by leogm99 on 22/5/21.
//

#ifndef TP3_SERVER_COMMANDHANDLER_H
#define TP3_SERVER_COMMANDHANDLER_H


#include <vector>
#include "server_ClientMonitor.h"
#include "server_ClientHandler.h"

class CommandHandler {
private:
    static const uint8_t crear = 0x6e;
    static const uint8_t listar = 0x6c;
    static const uint8_t unirse = 0x6a;
    static const uint8_t jugar = 0x70;
protected:
    std::vector<unsigned char>& msg;
    unsigned char& clientSymbol;
    std::string& gameName;
    ClientMonitor& monitor;
public:
    CommandHandler(std::vector<unsigned char>& message,
                   unsigned char& clientSymbol,
                   std::string& gameName,
                   ClientMonitor& monitor);

    virtual std::string operator()() = 0;

    static std::unique_ptr<CommandHandler>
    getCommand(std::vector<unsigned char>& message,
               unsigned char& clientSymbol,
               std::string& gameName,
               ClientMonitor &monitor);

    virtual ~CommandHandler();
};


#endif //TP3_SERVER_COMMANDHANDLER_H
