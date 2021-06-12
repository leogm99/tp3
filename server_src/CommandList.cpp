#include "CommandList.h"
#include <string>

const std::string& CommandList::operator()() {
    shouldNotify = true;
    return monitor.listGames();
}

CommandList::CommandList(CommandList &&other) noexcept
: CommandHandler(std::move(other)){
}

CommandList &CommandList::operator=(CommandList &&other) noexcept {
    if (this == &other){
        return *this;
    }

    CommandHandler::operator=(std::move(other));
    return *this;
}
