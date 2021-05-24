//
// Created by leogm99 on 22/5/21.
//

#include "server_ClientMonitor.h"

ClientMonitor::ClientMonitor(){
    namesList = "Partidas:\n";
}

const std::string& ClientMonitor::listGames() {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    for (const auto& game : games){
        namesList += " - " + game.first + "\n";
    }
    return namesList;
}

GameMonitor &ClientMonitor::accessGame(const std::string &game) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    try {
        return games.at(game).first;
    } catch(const std::exception& e){
        throw std::string("Invalid Game");
    }
}

const std::string& ClientMonitor::createGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it == games.end()){

        games.emplace(std::make_pair(
                gameName, std::make_pair(GameMonitor(), true)
        ));

        return games.at(gameName).first.showBoard('O');
    }
    throw std::string("Game already exists");
}

void ClientMonitor::joinGame(const std::string &gameName) {
    std::lock_guard<std::mutex> lockGuard(clientsMutex);
    auto it = games.find(gameName);
    if (it == games.end()){
        throw std::invalid_argument("el juego no existe");
    }
    if (!it->second.second){
        throw std::invalid_argument("Game is already full, vuelva prontos");
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
