//
// Created by leogm99 on 22/5/21.
//

#ifndef TP3_SERVER_GAMEMONITOR_H
#define TP3_SERVER_GAMEMONITOR_H

#include <mutex>
#include <condition_variable>
#include "server_BoardFileHandler.h"
#include "server_BoardView.h"
#include "server_Board.h"

class GameMonitor {
private:
    std::mutex gameLock;
    std::condition_variable turn;
    unsigned char currPlayer;
    Board gameBoard;
public:
    GameMonitor();

    GameMonitor(const GameMonitor& other) = delete;
    GameMonitor& operator=(const GameMonitor& other) = delete;

    GameMonitor(GameMonitor&& other) noexcept;
    GameMonitor& operator=(GameMonitor&& other) noexcept;
    void play(unsigned char clientSymbol, unsigned int col, unsigned int row);
    ~GameMonitor();
};


#endif //TP3_SERVER_GAMEMONITOR_H
