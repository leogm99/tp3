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
#include "server_ClientHandler.h"

class GameMonitor {
private:
    std::mutex gameLock;
    std::condition_variable turn;
    unsigned char currPlayer;
    Board gameBoard;
public:
    GameMonitor();
    void play(ClientHandler& cli, unsigned int col, unsigned int row);
    ~GameMonitor();
};


#endif //TP3_SERVER_GAMEMONITOR_H
