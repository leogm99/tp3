//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandJoin.h"

std::string CommandJoin::operator()() {
    std::string gameName(msg.begin() + 3, msg.end());
    monitor.joinGame(gameName);
    return std::string();
}
