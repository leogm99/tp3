//
// Created by leogm99 on 19/5/21.
//

#include "server_BoardView.h"
#include <string>
#include <utility>


BoardView::BoardView()
: fh(std::move(BoardFileHandler("board.txt"))){
    boardView = std::move(fh.getPlainBoard());
}

const std::string& BoardView::print() {
    return boardView;
}

void BoardView::updateAt(unsigned int col, unsigned int row, char symbol) {
    unsigned int mapping = fh.getMapping(col, row);
    boardView[mapping] = symbol;
}

BoardView::BoardView(BoardView &&other) noexcept
: boardView(std::move(other.boardView)), fh(std::move(other.fh)){
}

BoardView &BoardView::operator=(BoardView &&other) noexcept {
    boardView = std::move(other.boardView);
    return *this;
}

