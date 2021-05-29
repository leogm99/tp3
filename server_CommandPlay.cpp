#include "server_CommandPlay.h"
#include <iostream>
#include <string>

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
