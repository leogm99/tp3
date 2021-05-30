#ifndef TP3_SERVER_CLIENTMONITOR_H
#define TP3_SERVER_CLIENTMONITOR_H

#include "GameMonitor.h"
#include <string>
#include <mutex>
#include <utility>
#include <map>


class ClientMonitor {
private:
    std::map<std::string, std::pair<GameMonitor, bool>> games;
    std::mutex clientsMutex;
    std::string namesList;
public:
    ClientMonitor();

    const std::string& listGames();
    const std::string& createGame(const std::string& gameName);
    void joinGame(const std::string& gameName);
    GameMonitor& accessGame(const std::string& game);

    ~ClientMonitor();

    bool killGameIfJoinable(const std::string &basicString);
};


#endif //TP3_SERVER_CLIENTMONITOR_H
