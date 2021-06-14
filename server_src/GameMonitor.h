#ifndef TP3_SERVER_GAMEMONITOR_H
#define TP3_SERVER_GAMEMONITOR_H

#include <string>
#include <mutex>
#include <condition_variable>
#include "BoardView.h"
#include "Board.h"

class GameMonitor {
private:
    std::mutex gameLock;
    std::condition_variable turn;
    unsigned char currPlayer;
    Board gameBoard;
    bool handleGameDoneMessage(std::string& msgGameDone);

    GameMonitor(GameMonitor&& other,
                const std::lock_guard<std::mutex>& otherMutex) noexcept;

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

    void waitIfNotTurnAndGameNotDone(unsigned char clientSymbol,
                                     std::unique_lock<std::mutex> &lock);
    bool gameIsDone(std::string& gameDoneMsg);
    void updateCurrentPlayer();
};


#endif //TP3_SERVER_GAMEMONITOR_H
