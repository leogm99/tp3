#include <string>
#include "CommandJoin.h"
#include "../common_src/CommandException.h"

const std::string& CommandJoin::operator()() {
    if (!gameName.empty()){
        throw CommandException(HAS_GAME, gameName.c_str());
    }
    std::string searchedGame(msg.begin() + 3, msg.end());
    monitor.joinGame(searchedGame);
    GameMonitor& game = monitor.accessGame(searchedGame);
    gameName = searchedGame;
    clientSymbol = 'X';
    playing = true;
    return game.showBoard(clientSymbol);
}

CommandJoin::CommandJoin(CommandJoin &&other) noexcept
: CommandHandler(std::move(other)){
}

CommandJoin &CommandJoin::operator=(CommandJoin &&other) noexcept {
    if (this == &other){
        return *this;
    }
    CommandHandler::operator=(std::move(other));
    return *this;
}
