#include "CommandPlay.h"
#include <iostream>
#include <string>
#include <utility>

const std::string& CommandPlay::operator()() {
    unsigned char colRow = msg.at(1);
    unsigned char col = ((colRow & 0xf0) >> 4) + 1;
    unsigned char row = (colRow & 0xf) + 1;
    GameMonitor& g = monitor.accessGame(gameName);
    gameBoardStatus.clear();
    gameBoardStatus += g.play(clientSymbol, col, row, msgGameDone);
    if (!msgGameDone.empty()){
        gameBoardStatus += msgGameDone;
        clientIsDead = true;
        playing = false;
    }
    return gameBoardStatus;
}

CommandPlay::CommandPlay(CommandPlay &&other) noexcept
: CommandHandler(std::move(other)),
  gameBoardStatus(std::move(other.gameBoardStatus)),
  msgGameDone(std::move(other.msgGameDone)){
}

CommandPlay &CommandPlay::operator=(CommandPlay &&other) noexcept {
    if (this == &other){
        return *this;
    }
    this->gameBoardStatus = std::move(other.gameBoardStatus);
    this->msgGameDone = std::move(other.msgGameDone);

    CommandHandler::operator=(std::move(other));
    return *this;
}
