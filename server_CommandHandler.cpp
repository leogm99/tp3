//
// Created by leogm99 on 22/5/21.
//

#include "server_CommandHandler.h"
#include "server_CommandPlay.h"
#include "server_CommandCreate.h"
#include "server_CommandJoin.h"
#include "server_CommandList.h"


CommandHandler::CommandHandler(std::vector<unsigned char>& message, unsigned char& clientSymbol,
                               std::string& gameName, ClientMonitor &monitor, bool& clientDead)
: msg(message), clientSymbol(clientSymbol),
gameName(gameName), monitor(monitor), clientIsDead(clientDead){
}


std::unique_ptr<CommandHandler>
CommandHandler::getCommand(std::vector<unsigned char>& message,
                           unsigned char& clientSymbol,
                           std::string& gameName,
                           ClientMonitor &monitor,
                           bool& clientDead) {
    switch (message.at(0)){
        case jugar:
            return std::unique_ptr<CommandHandler>
            (new CommandPlay(message, clientSymbol, gameName, monitor, clientDead));
        case crear:
            return std::unique_ptr<CommandHandler>
            (new CommandCreate(message, clientSymbol, gameName, monitor, clientDead));
        case listar:
            return std::unique_ptr<CommandHandler>
            (new CommandList(message, clientSymbol, gameName, monitor, clientDead));
        case unirse:
            return std::unique_ptr<CommandHandler>
            (new CommandJoin(message, clientSymbol, gameName, monitor, clientDead));
    }
    throw std::exception();
}

CommandHandler::~CommandHandler() {
}
