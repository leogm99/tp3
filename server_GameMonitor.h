#ifndef TP3_SERVER_GAMEMONITOR_H
#define TP3_SERVER_GAMEMONITOR_H

#include <string>
#include <mutex>
#include <condition_variable>
#include "server_BoardView.h"
#include "server_Board.h"

class GameMonitor {
private:
    std::mutex gameLock;
    std::condition_variable turn;
    unsigned char currPlayer;
    Board gameBoard;
    bool handleGameDoneMessage(std::string& msgGameDone);
public:
    GameMonitor();

    GameMonitor(const GameMonitor& other) = delete;
    GameMonitor& operator=(const GameMonitor& other) = delete;

    GameMonitor(GameMonitor&& other) noexcept;
    GameMonitor& operator=(GameMonitor&& other) noexcept;

    const std::string& play(unsigned char clientSymbol,
                            unsigned int col,
                            unsigned int row,
                            std::string& gameDoneMsg);
    const std::string& showBoard(unsigned char clientSymbol);

    ~GameMonitor();
};


#endif //TP3_SERVER_GAMEMONITOR_H
