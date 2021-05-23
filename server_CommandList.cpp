//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandList.h"

std::string CommandList::operator()() {
    return std::move(monitor.listGames());
}
