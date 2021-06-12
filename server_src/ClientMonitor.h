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
    bool sendingNamesList;
    std::condition_variable gamesListSend;

    ClientMonitor(ClientMonitor&& other,
                  const std::lock_guard<std::mutex>& otherLock);

public:
    ClientMonitor();

    ClientMonitor(const ClientMonitor& other) = delete;
    ClientMonitor& operator=(const ClientMonitor& other) = delete;

    ClientMonitor(ClientMonitor&& other) noexcept;
    ClientMonitor& operator=(ClientMonitor&& other) noexcept;

    const std::string& listGames();
    const std::string& createGame(const std::string& gameName);
    void joinGame(const std::string& gameName);
    GameMonitor& accessGame(const std::string& game);

    void notifyWaiting();
    ~ClientMonitor();

    bool killGameIfJoinable(const std::string &basicString);
};


#endif //TP3_SERVER_CLIENTMONITOR_H
