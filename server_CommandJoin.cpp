//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandJoin.h"

const std::string& CommandJoin::operator()() {
    if (!gameName.empty()){
        throw std::exception();
    }
    std::string searchedGame(msg.begin() + 3, msg.end());
    monitor.joinGame(searchedGame);
    GameMonitor& game = monitor.accessGame(searchedGame);
    return game.showBoard(clientSymbol);
}
