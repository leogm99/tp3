#include <string>
#include "server_GameMonitor.h"

GameMonitor::GameMonitor()
: gameBoard(Board(
        BoardView())){
    currPlayer = 'O';
}

const std::string& GameMonitor::play(unsigned char clientSymbol,
                                     unsigned int col,
                                     unsigned int row,
                                     std::string& gameDoneMsg) {
    std::unique_lock<std::mutex> lock(gameLock);
    // mientras que no sea el current player, espero
    while ((clientSymbol != currPlayer) && gameBoard.getWinner() == 'N'){
        turn.wait(lock);
    }

    if (handleGameDoneMessage(gameDoneMsg)){
        turn.notify_all();
        return gameBoard.print();
    }
    gameBoard.placeAt(col, row);

    if (handleGameDoneMessage(gameDoneMsg)){
        currPlayer = gameBoard.getCurrentPlayer();
        turn.notify_all();
        return gameBoard.print();
    } else {
        currPlayer = gameBoard.getCurrentPlayer();
        turn.notify_all();
        while ((clientSymbol != currPlayer) && gameBoard.getWinner() == 'N'){
            turn.wait(lock);
        }
    }
    // el tablero actualiza al proximo jugador
    // por ende lo actualizo aqui
    // espero nuevamente a que el otro jugador haga una movida
    // asi puedo devolver el tablero
    if (handleGameDoneMessage(gameDoneMsg)){
        return gameBoard.print();
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

bool GameMonitor::handleGameDoneMessage(std::string &msgGameDone) {
    unsigned char gameDone;
    if ((gameDone = gameBoard.getWinner()) != 'N') {
        if (gameDone == currPlayer) {
            msgGameDone += "Felicitaciones! Ganaste!\n";
        } else if (gameDone != 'E'){
            msgGameDone += "Has perdido. Segui intentando!\n";
        } else {
            msgGameDone += "La partida ha terminado en empate\n";
        }
        return true;
    }
    return false;
}
