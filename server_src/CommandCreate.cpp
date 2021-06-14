#include <string>
#include "CommandCreate.h"
#include "../common_src/CommandException.h"

const std::string& CommandCreate::operator()() {
    if (!gameName.empty()){
        throw CommandException(HAS_GAME, gameName.c_str());
    }
    gameName.assign(msg.begin() + 3, msg.end());
    try {
        const std::string& board = monitor.createGame(gameName);
        clientSymbol = 'O';
        playing = true;
        return board;
    } catch(const std::exception& e){
        gameName.clear();
        clientSymbol = 'N';
        playing = false;
        throw;
    }
}

CommandCreate::CommandCreate(CommandCreate &&other) noexcept
: CommandHandler(std::move(other)){
}

CommandCreate &CommandCreate::operator=(CommandCreate &&other) noexcept {
    if (this == &other){
        return *this;
    }

    CommandHandler::operator=(std::move(other));
    return *this;
}
