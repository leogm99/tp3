//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandJoin.h"

const std::string& CommandJoin::operator()() {
    if (!gameName.empty()){
        throw std::invalid_argument("You are already queued for a game\n");
    }
    std::string searchedGame(msg.begin() + 3, msg.end());
    monitor.joinGame(searchedGame);
    GameMonitor& game = monitor.accessGame(searchedGame);
    gameName = searchedGame;
    clientSymbol = 'X';
    return game.showBoard(clientSymbol);
}
