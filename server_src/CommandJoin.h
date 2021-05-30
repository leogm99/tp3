#ifndef TP3_SERVER_COMMANDJOIN_H
#define TP3_SERVER_COMMANDJOIN_H

#include <string>
#include "CommandHandler.h"

class CommandJoin : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;
};


#endif //TP3_SERVER_COMMANDJOIN_H
