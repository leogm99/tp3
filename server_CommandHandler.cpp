//
// Created by leogm99 on 22/5/21.
//

#include "server_CommandHandler.h"
#include "server_CommandPlay.h"
#include "server_CommandCreate.h"
#include "server_CommandJoin.h"
#include "server_CommandList.h"


CommandHandler::CommandHandler(std::vector<unsigned char>& message, ClientHandler &handler, ClientMonitor &monitor)
: msg(message), clientHandler(handler), monitor(monitor){
}


CommandHandler *CommandHandler::
getCommand(std::vector<unsigned char>& message, ClientHandler &handler,
           ClientMonitor &monitor) {
    switch (message.at(0)){
        case jugar:
            return new CommandPlay(message, handler, monitor);
        case crear:
            return new CommandCreate(message, handler, monitor);
        case listar:
            return new CommandList(message, handler, monitor);
        case unirse:
            return new CommandJoin(message, handler, monitor);
    }
    throw std::exception();
}

CommandHandler::~CommandHandler() {
}
