//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_SERVER_COMMANDPLAY_H
#define TP3_SERVER_COMMANDPLAY_H

#include <vector>
#include "server_Board.h"
#include "server_CommandHandler.h"

class CommandPlay : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;
};


#endif //TP3_SERVER_COMMANDPLAY_H
