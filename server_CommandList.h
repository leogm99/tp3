//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_SERVER_COMMANDLIST_H
#define TP3_SERVER_COMMANDLIST_H

#include "server_CommandHandler.h"

class CommandList : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    std::string operator()() override;
};


#endif //TP3_SERVER_COMMANDLIST_H
