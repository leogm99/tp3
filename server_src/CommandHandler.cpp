#include "CommandHandler.h"
#include "CommandPlay.h"
#include "CommandCreate.h"
#include "CommandJoin.h"
#include "CommandList.h"
#include "../common_src/CommandException.h"
#include "../common_src/Macros.h"
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
playing(playing),
shouldNotify(false){
}


std::unique_ptr<CommandHandler>
CommandHandler::getCommand(std::vector<unsigned char>& message,
                           unsigned char& clientSymbol,
                           std::string& gameName,
                           ClientMonitor &monitor,
                           std::atomic_bool& clientDead,
                           std::atomic_bool& playing) {
    switch (message.at(0)){
        case JUGAR:
            return std::unique_ptr<CommandHandler>
            (new CommandPlay(message, clientSymbol,gameName,
                             monitor,clientDead, playing));
        case CREAR:
            return std::unique_ptr<CommandHandler>
            (new CommandCreate(message, clientSymbol, gameName,
                               monitor, clientDead, playing));
        case LISTAR:
            return std::unique_ptr<CommandHandler>
            (new CommandList(message, clientSymbol, gameName,
                             monitor, clientDead, playing));
        case UNIRSE:
            return std::unique_ptr<CommandHandler>
            (new CommandJoin(message, clientSymbol, gameName,
                             monitor, clientDead, playing));
        default:
            throw CommandException(INVAL_COMMAND);
    }
}

bool CommandHandler::notify() {
    return shouldNotify;
}

CommandHandler::~CommandHandler() {
}

CommandHandler::CommandHandler(CommandHandler &&other) noexcept
: msg(other.msg),
  clientSymbol(other.clientSymbol),
  gameName(other.gameName),
  monitor(other.monitor),
  clientIsDead(other.clientIsDead),
  playing(other.playing),
  shouldNotify(other.shouldNotify){
}

CommandHandler &CommandHandler::operator=(CommandHandler &&other) noexcept {
    if (this == &other){
        return *this;
    }

    this->clientSymbol = other.clientSymbol;
    this->shouldNotify = other.shouldNotify;
    return *this;
}
