#include "CommandList.h"
#include <string>

const std::string& CommandList::operator()() {
    return monitor.listGames();
}
