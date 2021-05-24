//
// Created by leogm99 on 22/5/21.
//

#ifndef TP3_SERVER_CLIENTMONITOR_H
#define TP3_SERVER_CLIENTMONITOR_H

#include "server_GameMonitor.h"
#include "server_BoardFileHandler.h"
#include <string>
#include <mutex>


class ClientMonitor {
private:
    std::map<std::string, std::pair<GameMonitor, bool>> games;
    std::mutex clientsMutex;
public:
    ClientMonitor();

    std::string listGames();
    void createGame(std::string& gameName);
    void joinGame(const std::string& gameName);
    GameMonitor& accessGame(const std::string& game);

    void signalGameDone(const std::string& gameName);
    ~ClientMonitor();
};


#endif //TP3_SERVER_CLIENTMONITOR_H
