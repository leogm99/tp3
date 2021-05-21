//
// Created by leogm99 on 19/5/21.
//

#include "server_BoardView.h"
#include <string>
#include <utility>


BoardView::BoardView(const BoardFileHandler& fh)
: fh(fh){
    boardView = std::move(fh.getPlainBoard());
}

void BoardView::print() {
    std::cout << boardView;
}

void BoardView::updateAt(unsigned int col, unsigned int row, char symbol) {
    unsigned int mapping = fh.getMapping(col, row);
    boardView[mapping] = symbol;
}

BoardView::BoardView(BoardView &&other) noexcept
: boardView(std::move(other.boardView)),
  fh(other.fh){
}

BoardView &BoardView::operator=(BoardView &&other) noexcept {
    boardView = std::move(other.boardView);
    return *this;
}

