#include "../common_src/Macros.h"
#include "BoardView.h"
#include <string>
#include <utility>
#include <map>

BoardView::BoardView()
: boardView(BOARD),
  boardMapping(createMap()){
}

const std::string& BoardView::print() {
    return boardView;
}

void BoardView::updateAt(unsigned int col, unsigned int row, char symbol) {
    unsigned int mapping = getMapping(col, row);
    boardView[mapping] = symbol;
}

BoardView::BoardView(BoardView &&other) noexcept
: boardView(std::move(other.boardView)),
  boardMapping(std::move(other.boardMapping)){
}

BoardView &BoardView::operator=(BoardView &&other) noexcept {
    if (this == &other){
        return *this;
    }
    boardView = std::move(other.boardView);
    boardMapping = std::move(other.boardMapping);
    return *this;
}

unsigned int BoardView::
getMapping(unsigned int col, unsigned int row) const {
    return boardMapping.at(std::make_pair(col, row));
}
