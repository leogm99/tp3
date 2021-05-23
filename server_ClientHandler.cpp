//
// Created by leogm99 on 22/5/21.
//

#include "server_ClientHandler.h"
#include "server_ClientMonitor.h"
#include "common_Socket.h"

ClientHandler::ClientHandler(ClientMonitor& aMonitor, Socket clientSocket)
: monitor(aMonitor), clientSocket(std::move(clientSocket)) {
    symbol = 'N';
    game = "";
}

void ClientHandler::run() {
}

ClientHandler::~ClientHandler() {
}
