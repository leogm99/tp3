#include <vector>
#include <string>
#include <memory>
#include <utility>
#include "ClientHandler.h"
#include "ClientMonitor.h"
#include "../common_src/Socket.h"
#include "CommandHandler.h"

ClientHandler::ClientHandler(ClientMonitor& aMonitor,
                             ServProtocol& protocol,
                             Socket clientSocket)
:  monitor(aMonitor), servProtocol(protocol),
   clientSocket(std::move(clientSocket)),
   dead(false), playing(false){
    symbol = 'N';
}

void ClientHandler::run() {
    std::vector <unsigned char> msg;
    while (!dead){
        msg = servProtocol.receive(clientSocket);
        if (msg.empty()){
            break;
        }
        std::unique_ptr<CommandHandler> cmd =
                CommandHandler::
        getCommand(msg, symbol, game, monitor, dead, playing);
        try {
            const std::string& msgBack = cmd->operator()();
            if (servProtocol.send(clientSocket, msgBack) < 0){
                if (cmd->notify()){
                    monitor.notifyWaiting();
                }
                break;
            }
            if (cmd->notify()){
                monitor.notifyWaiting();
            }
        } catch(const std::invalid_argument& e){
            servProtocol.send(clientSocket, e.what());
        } catch(const std::exception& e){
            servProtocol.send(clientSocket, e.what());
        }
    }
    dead = true;
}

ClientHandler::~ClientHandler() {
}

bool ClientHandler::isDead() {
    return dead;
}

ClientHandler::ClientHandler(ClientHandler &&other) noexcept
: Thread(std::move(other)),
  monitor(other.monitor),
  servProtocol(other.servProtocol),
  clientSocket(std::move(other.clientSocket)),
  game(std::move(other.game)),
  dead(false){
    other.game = "";
    symbol = other.symbol;
    other.symbol = 'N';
    if (!game.empty()){
        playing = true;
    }
}

ClientHandler &ClientHandler::operator=(ClientHandler &&other) noexcept {
    if (this == &other){
        return *this;
    }
    clientSocket = std::move(other.clientSocket);
    game = std::move(other.game);
    other.game = "";
    symbol = other.symbol;
    dead = false;
    if (!game.empty()){
        playing = true;
    }
    return *this;
}

void ClientHandler::killIfIdle() {
    if (!playing) {
        dead = true;
        clientSocket.shutdown();
    } else{
        if (monitor.killGameIfJoinable(game)){
            dead = true;
            clientSocket.shutdown();
        }
    }
}
