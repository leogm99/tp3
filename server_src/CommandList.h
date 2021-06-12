#ifndef TP3_SERVER_COMMANDLIST_H
#define TP3_SERVER_COMMANDLIST_H

#include <string>
#include "CommandHandler.h"

class CommandList : public CommandHandler {
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;

    CommandList(const CommandList& other) = delete;
    CommandList& operator=(const CommandList& other) = delete;

    CommandList(CommandList&& other) noexcept;
    CommandList& operator=(CommandList&& other) noexcept;
};


#endif //TP3_SERVER_COMMANDLIST_H
