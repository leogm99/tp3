#include <string>
#include "CommandCreate.h"

const std::string& CommandCreate::operator()() {
    if (!gameName.empty()){
        throw std::invalid_argument("You are already queued for a game\n");
    }
    gameName.assign(msg.begin() + 3, msg.end());
    try {
        const std::string& board = monitor.createGame(gameName);
        clientSymbol = 'O';
        playing = true;
        return board;
    } catch(const std::exception& e){
        gameName.clear();
        throw std::invalid_argument("Game already exists\n");
    }
}
