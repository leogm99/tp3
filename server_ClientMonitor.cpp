//
// Created by leogm99 on 22/5/21.
//

#include "server_ClientMonitor.h"

ClientMonitor::ClientMonitor()
: fh("board.txt"){
}

std::string ClientMonitor::listGames() {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    std::string names("Partidas:");
    for (const auto& game : games){
        names.append(game.first);
    }
    return names;
}

GameMonitor &ClientMonitor::accessGame(const std::string &game) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    try {
        GameMonitor& g = games.at(game).first;
        return g;
    } catch(const std::exception& e){
        throw std::string("Invalid Game");
    }
}

void ClientMonitor::createGame(const std::string &gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it == games.end()){
        games[gameName] = std::make_pair(GameMonitor(), true);
        return;
    }
    throw std::string("Game already exists");
}

void ClientMonitor::joinGame(const std::string &gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it == games.end()){
        throw std::string("Game does not exist");
    }
    if (!it->second.second){
        throw std::string("Game is already full, vuelva prontos");
    }
    games[gameName].second = false; // nadie mas se puede unir;
}

void ClientMonitor::signalGameDone(const std::string &gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it != games.end()){
        games.erase(it);
        return;
    }
    throw std::string("Game to erase does not exist");
}

ClientMonitor::~ClientMonitor() {
}
