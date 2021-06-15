#include <string>
#include <utility>
#include "../common_src/Macros.h"
#include "GameMonitor.h"

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

    waitIfNotTurnAndGameNotDone(clientSymbol, lock);

    if (gameIsDone(gameDoneMsg)){
        return gameBoard.print();
    }

    gameBoard.placeAt(col, row);

    if (gameIsDone(gameDoneMsg)){
        updateCurrentPlayer();
        return gameBoard.print();
    } else {
        updateCurrentPlayer();
        waitIfNotTurnAndGameNotDone(clientSymbol, lock);
    }

    handleGameDoneMessage(gameDoneMsg);
    return gameBoard.print();
}

void GameMonitor::
waitIfNotTurnAndGameNotDone(unsigned char clientSymbol,
                            std::unique_lock<std::mutex> &lock) {
    while ((clientSymbol != currPlayer) && gameBoard.getWinner() == 'N'){
        turn.wait(lock);
    }
}

GameMonitor::~GameMonitor() {
}

GameMonitor::GameMonitor(GameMonitor &&other) noexcept
: GameMonitor(std::move(other),
              std::lock_guard<std::mutex>(other.gameLock)){
}

GameMonitor &GameMonitor::operator=(GameMonitor &&other) noexcept {
    std::lock_guard<std::mutex> lock(other.gameLock);
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
            msgGameDone += MSGWON;
        } else if (gameDone != 'E'){
            msgGameDone += MSGLOST;
        } else {
            msgGameDone += MSGTIE;
        }
        return true;
    }
    return false;
}

GameMonitor::GameMonitor(GameMonitor &&other,
                         const std::lock_guard<std::mutex> &otherMutex) noexcept
: currPlayer(other.currPlayer),
  gameBoard(std::move(other.gameBoard)){
}

bool GameMonitor::gameIsDone(std::string &gameDoneMsg) {
    if (handleGameDoneMessage(gameDoneMsg)){
        turn.notify_all();
        return true;
    }
    return false;
}

void GameMonitor::updateCurrentPlayer() {
    currPlayer = gameBoard.getCurrentPlayer();
    turn.notify_all();
}
