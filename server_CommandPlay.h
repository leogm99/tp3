#ifndef TP3_SERVER_COMMANDPLAY_H
#define TP3_SERVER_COMMANDPLAY_H

#include <string>
#include <vector>
#include "server_Board.h"
#include "server_CommandHandler.h"

class CommandPlay : public CommandHandler {
private:
    std::string gameBoardStatus;
    std::string msgGameDone;
public:
    using CommandHandler::CommandHandler;
    const std::string& operator()() override;
};


#endif //TP3_SERVER_COMMANDPLAY_H
