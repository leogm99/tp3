//
// Created by leogm99 on 22/5/21.
//

#include "server_ClientHandler.h"
#include "server_ClientMonitor.h"
#include "common_Socket.h"
#include "server_CommandHandler.h"

ClientHandler::ClientHandler(ClientMonitor& aMonitor, ServProtocol& protocol, Socket clientSocket)
:  monitor(aMonitor), servProtocol(protocol), clientSocket(std::move(clientSocket)) {
    symbol = 'N';
    game = "";
    dead = false;
}

void ClientHandler::run() {
    std::vector <unsigned char> msg;
    while (!dead){
        msg = std::move(servProtocol.receive(clientSocket));
        std::unique_ptr<CommandHandler> cmd =
                CommandHandler::
        getCommand(msg, symbol, game, monitor);
        const std::string& msgBack = cmd->operator()();
        servProtocol.send(clientSocket, msgBack);
    }
}

ClientHandler::~ClientHandler() {
    dead = true;
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
}

ClientHandler &ClientHandler::operator=(ClientHandler &&other) noexcept {
    clientSocket = std::move(other.clientSocket);
    game = std::move(other.game);
    other.game = "";
    symbol = other.symbol;
    other.symbol = 'N';
    return *this;
}
