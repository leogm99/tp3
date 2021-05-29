//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandCreate.h"

const std::string& CommandCreate::operator()() {
    if (!gameName.empty()){
        throw std::invalid_argument("You are already queued for a game\n");
    }
    gameName.assign(msg.begin() + 3, msg.end());
    const std::string& board = monitor.createGame(gameName);
    clientSymbol = 'O';
    playing = true;
    return board;
}
