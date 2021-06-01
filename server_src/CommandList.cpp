#include "CommandList.h"
#include <string>

const std::string& CommandList::operator()() {
    shouldNotify = true;
    return monitor.listGames();
}
