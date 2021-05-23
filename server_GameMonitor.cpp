//
// Created by leogm99 on 22/5/21.
//

#include "server_GameMonitor.h"

GameMonitor::GameMonitor()
: gameBoard(std::move(BoardView(BoardFileHandler("board.txt")))){
    currPlayer = 'O';
}

void GameMonitor::play(ClientHandler &cli, unsigned int col, unsigned int row) {
    std::unique_lock<std::mutex> lock(gameLock);
    // mientras que no sea el current player, espero
    while (!cli.is(currPlayer)){
        turn.wait(lock);
    }
    try {
        gameBoard.placeAt(col, row);
    } catch (const std::exception& e){
        throw e;
    }
    currPlayer = gameBoard.getCurrentPlayer();
    // no se despertaria hasta que el actual salga de scope
    turn.notify_all();
}

GameMonitor::~GameMonitor() {
}
