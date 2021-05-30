#include "CommandHandler.h"
#include "CommandPlay.h"
#include "CommandCreate.h"
#include "CommandJoin.h"
#include "CommandList.h"
#include <string>
#include <vector>
#include <memory>

CommandHandler::CommandHandler(std::vector<unsigned char>& message,
                               unsigned char& clientSymbol,
                               std::string& gameName,
                               ClientMonitor &monitor,
                               std::atomic_bool& clientDead,
                               std::atomic_bool& playing)
: msg(message), clientSymbol(clientSymbol),
gameName(gameName),
monitor(monitor),
clientIsDead(clientDead),
playing(playing){
}


std::unique_ptr<CommandHandler>
CommandHandler::getCommand(std::vector<unsigned char>& message,
                           unsigned char& clientSymbol,
                           std::string& gameName,
                           ClientMonitor &monitor,
                           std::atomic_bool& clientDead,
                           std::atomic_bool& playing) {
    switch (message.at(0)){
        case jugar:
            return std::unique_ptr<CommandHandler>
            (new CommandPlay(message, clientSymbol,gameName,
                             monitor,clientDead, playing));
        case crear:
            return std::unique_ptr<CommandHandler>
            (new CommandCreate(message, clientSymbol, gameName,
                               monitor, clientDead, playing));
        case listar:
            return std::unique_ptr<CommandHandler>
            (new CommandList(message, clientSymbol, gameName,
                             monitor, clientDead, playing));
        case unirse:
            return std::unique_ptr<CommandHandler>
            (new CommandJoin(message, clientSymbol, gameName,
                             monitor, clientDead, playing));
    }
    throw std::exception();
}

CommandHandler::~CommandHandler() {
}
