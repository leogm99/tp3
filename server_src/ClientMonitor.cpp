#include <string>
#include <algorithm>
#include "ClientMonitor.h"

ClientMonitor::ClientMonitor()
:sendingNamesList(false){
}

const std::string& ClientMonitor::listGames() {
    std::unique_lock<std::mutex> lock(clientsMutex);
    while (sendingNamesList){
        gamesListSend.wait(lock);
    }
    namesList.clear();
    namesList = "Partidas:\n";
    auto it = games.begin();
    while (it != games.end()){
        namesList += " - " + (*it).first + "\n";
        ++it;
    }
    sendingNamesList = true;
    return namesList;
}

GameMonitor &ClientMonitor::accessGame(const std::string &game) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    try {
        return games.at(game).first;
    } catch(const std::exception& e){
        throw std::invalid_argument("Invalid Game\n");
    }
}

const std::string& ClientMonitor::createGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it == games.end()){
        games.emplace(std::make_pair(
                gameName,
                std::make_pair(GameMonitor(), true)));
        return games.at(gameName).first.showBoard('O');
    }
    throw std::invalid_argument("Game already exists\n");
}

void ClientMonitor::joinGame(const std::string &gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it == games.end()){
        throw std::invalid_argument("Game does not exist\n");
    }
    if (!it->second.second){
        throw std::invalid_argument("Game is already full, vuelva prontos\n");
    }
    games[gameName].second = false; // nadie mas se puede unir;
}

ClientMonitor::~ClientMonitor() {
}

bool ClientMonitor::killGameIfJoinable(const std::string &gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it != games.end() && it->second.second){
        games.erase(it);
        return true;
    }
    return false;
}

void ClientMonitor::notifyWaiting() {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    sendingNamesList = false;
    gamesListSend.notify_all();
}

ClientMonitor::ClientMonitor(ClientMonitor &&other) noexcept
: ClientMonitor(std::move(other),
                std::lock_guard<std::mutex>(other.clientsMutex)){
}

ClientMonitor &ClientMonitor::operator=(ClientMonitor &&other) noexcept {
    if (this == &other){
        return *this;
    }

    this->games = std::move(other.games);
    this->namesList = std::move(other.namesList);
    this->sendingNamesList = other.sendingNamesList;
    return *this;
}

ClientMonitor::ClientMonitor(ClientMonitor &&other,
                             const std::lock_guard<std::mutex> &otherLock)
: games(std::move(other.games)),
  namesList(std::move(other.namesList)),
  sendingNamesList(other.sendingNamesList){
}
