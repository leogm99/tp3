//
// Created by leogm99 on 22/5/21.
//

#include "server_GameMonitor.h"

GameMonitor::GameMonitor()
: gameBoard(Board(
        BoardView())){
    currPlayer = 'O';
}

const std::string& GameMonitor::play(unsigned char clientSymbol, unsigned int col, unsigned int row) {
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
    turn.notify_all();
    // espero nuevamente a que el otro jugador haga una movida
    // asi puedo devolver el tablero
    while (clientSymbol != currPlayer){
        turn.wait(lock);
    }
    // no se despertaria hasta que el actual salga de scope
    // pero cuando el del viejo turno salga, ya se puede jugar
    return gameBoard.print();
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

const std::string& GameMonitor::showBoard(unsigned char clientSymbol) {
    std::unique_lock<std::mutex> lock(gameLock);
    while (clientSymbol != currPlayer){
        turn.wait(lock);
    }
    return gameBoard.print();
}
