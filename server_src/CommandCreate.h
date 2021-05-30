#ifndef TP3_SERVER_COMMANDCREATE_H
#define TP3_SERVER_COMMANDCREATE_H

#include <string>
#include "CommandHandler.h"

class CommandCreate : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;
};


#endif //TP3_SERVER_COMMANDCREATE_H
