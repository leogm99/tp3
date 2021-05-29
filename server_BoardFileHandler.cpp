#include <iostream>
#include <string>
#include "server_BoardFileHandler.h"

BoardFileHandler::BoardFileHandler(const char *boardFile) :
boardMapping(std::move(createMap())){
    std::ifstream f(boardFile);
    if (!f.is_open()){
        throw BoardException("Could not open board file "
                             "shuting down");
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    plainBoard = std::move(buffer.str());
}

std::string BoardFileHandler::getPlainBoard() const {
    return plainBoard;
}

unsigned int BoardFileHandler::
getMapping(unsigned int col, unsigned int row) const {
    return boardMapping.at(std::make_pair(col, row));
}

BoardFileHandler::~BoardFileHandler() {
}

BoardFileHandler::BoardFileHandler(BoardFileHandler &&other) noexcept
: plainBoard(std::move(other.plainBoard)),
  boardMapping(std::move(other.boardMapping)){
}

BoardFileHandler &BoardFileHandler::
operator=(BoardFileHandler &&other) noexcept {
    if (this == &other){
        return *this;
    }
    plainBoard = std::move(other.plainBoard);
    boardMapping = std::move(other.boardMapping);
    return *this;
}
