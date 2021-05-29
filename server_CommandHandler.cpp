#include "server_CommandHandler.h"
#include "server_CommandPlay.h"
#include "server_CommandCreate.h"
#include "server_CommandJoin.h"
#include "server_CommandList.h"
#include <string>
#include <vector>

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
