#ifndef TP3_SERVER_COMMANDHANDLER_H
#define TP3_SERVER_COMMANDHANDLER_H

#include "../common_src/Macros.h"
#include <string>
#include <vector>
#include <atomic>
#include <memory>
#include "ClientMonitor.h"

// forward declaration
// necesito llamar a metodos del client desde aca
class ClientHandler;

class CommandHandler {
protected:
    std::vector<unsigned char>& msg;
    unsigned char& clientSymbol;
    std::string& gameName;
    ClientMonitor& monitor;
    std::atomic_bool& clientIsDead;
    std::atomic_bool& playing;
    bool shouldNotify;

public:
    CommandHandler(std::vector<unsigned char>& message,
                   unsigned char& clientSymbol,
                   std::string& gameName,
                   ClientMonitor& monitor,
                   std::atomic_bool& clientDead,
                   std::atomic_bool& playing);

    explicit CommandHandler(const ClientMonitor& other) = delete;
    CommandHandler& operator=(const ClientMonitor& other) = delete;

    CommandHandler(CommandHandler&& other) noexcept;
    CommandHandler& operator=(CommandHandler&& other) noexcept;

    virtual const std::string& operator()() = 0;

    static std::unique_ptr<CommandHandler>
    getCommand(std::vector<unsigned char>& message,
               unsigned char& clientSymbol,
               std::string& gameName,
               ClientMonitor &monitor,
               std::atomic_bool& clientDead,
               std::atomic_bool& playing);

    bool notify();

    virtual ~CommandHandler();
};


#endif //TP3_SERVER_COMMANDHANDLER_H
