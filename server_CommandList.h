#ifndef TP3_SERVER_COMMANDLIST_H
#define TP3_SERVER_COMMANDLIST_H

#include <string>
#include "server_CommandHandler.h"

class CommandList : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;
};


#endif //TP3_SERVER_COMMANDLIST_H
