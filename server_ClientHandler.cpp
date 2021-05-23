//
// Created by leogm99 on 22/5/21.
//

#include "server_ClientHandler.h"

ClientHandler::ClientHandler(ClientMonitor& aMonitor)
: monitor(aMonitor){
    symbol = 'N';
}

bool ClientHandler::is(unsigned char aSymbol) {
    return this->symbol == aSymbol;
}

ClientHandler::~ClientHandler() {
}

