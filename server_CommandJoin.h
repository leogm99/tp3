//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_SERVER_COMMANDJOIN_H
#define TP3_SERVER_COMMANDJOIN_H


#include "server_CommandHandler.h"

class CommandJoin : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;
};


#endif //TP3_SERVER_COMMANDJOIN_H
