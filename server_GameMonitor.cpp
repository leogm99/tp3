//
// Created by leogm99 on 22/5/21.
//

#include "server_GameMonitor.h"

GameMonitor::GameMonitor()
: gameBoard(std::move(BoardView(BoardFileHandler("board.txt")))){
    currPlayer = 'O';
}

void GameMonitor::play(unsigned char clientSymbol, unsigned int col, unsigned int row) {
    std::unique_lock<std::mutex> lock(gameLock);
    // mientras que no sea el current player, espero
    while (clientSymbol != currPlayer){
        turn.wait(lock);
    }
    try {
        gameBoard.placeAt(col, row);
    } catch (const std::exception& e){
        throw e;
    }
    // el tablero actualiza al proximo jugador
    // por ende lo actualizo aqui
    currPlayer = gameBoard.getCurrentPlayer();
    // no se despertaria hasta que el actual salga de scope
    // pero cuando el del viejo turno salga, ya se puede jugar
    turn.notify_all();
}

GameMonitor::~GameMonitor() {
}

GameMonitor::GameMonitor(GameMonitor &&other) noexcept
: gameBoard(std::move(other.gameBoard)){
    this->currPlayer = other.currPlayer;
    other.currPlayer = 'N';
}

GameMonitor &GameMonitor::operator=(GameMonitor &&other) noexcept {
    this->gameBoard = std::move(other.gameBoard);
    this->currPlayer = other.currPlayer;
    other.currPlayer = 'N';
    return *this;
}
