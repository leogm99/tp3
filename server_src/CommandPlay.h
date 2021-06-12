#ifndef TP3_SERVER_COMMANDPLAY_H
#define TP3_SERVER_COMMANDPLAY_H

#include <string>
#include <vector>
#include "Board.h"
#include "CommandHandler.h"

class CommandPlay : public CommandHandler {
private:
    std::string gameBoardStatus;
    std::string msgGameDone;
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;

    CommandPlay(const CommandPlay& other) = delete;
    CommandPlay& operator=(const CommandPlay& other) = delete;

    CommandPlay(CommandPlay&& other) noexcept;
    CommandPlay& operator=(CommandPlay&& other) noexcept;

};


#endif //TP3_SERVER_COMMANDPLAY_H
