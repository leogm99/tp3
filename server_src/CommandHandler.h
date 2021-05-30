#ifndef TP3_SERVER_COMMANDHANDLER_H
#define TP3_SERVER_COMMANDHANDLER_H

#include <string>
#include <vector>
#include <atomic>
#include <memory>
#include "ClientMonitor.h"

// forward declaration
// necesito llamar a metodos del client desde aca
class ClientHandler;

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
    std::atomic_bool& clientIsDead;
    std::atomic_bool& playing;

public:
    CommandHandler(std::vector<unsigned char>& message,
                   unsigned char& clientSymbol,
                   std::string& gameName,
                   ClientMonitor& monitor,
                   std::atomic_bool& clientDead,
                   std::atomic_bool& playing);

    virtual const std::string& operator()() = 0;

    static std::unique_ptr<CommandHandler>
    getCommand(std::vector<unsigned char>& message,
               unsigned char& clientSymbol,
               std::string& gameName,
               ClientMonitor &monitor,
               std::atomic_bool& clientDead,
               std::atomic_bool& playing);

    virtual ~CommandHandler();
};


#endif //TP3_SERVER_COMMANDHANDLER_H
