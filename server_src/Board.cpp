#include "Board.h"
#include "BoardException.h"
#include <string>
#include <utility>
#include <algorithm>

Board::Board(BoardView bv)
: bv(std::move(bv)), currentSymbol('O') {
    rawBoard.fill(0);
    aWinner = 'N';
}

bool Board::isOccupied(unsigned int col, unsigned int row) const {
    char currentCell = rawBoard.at(3 * (col - 1) + row - 1);
    return (currentCell == 'O' || currentCell == 'X');
}

bool Board::isValidMove(unsigned int col, unsigned int row) const {
    if (col < 1 || col > 3) return false;
    if (row < 1 || row > 3) return false;
    if (isOccupied(col, row)) return false;
    return true;
}

void Board::updateSymbol() {
    currentSymbol = (currentSymbol == 'O' ? 'X' : 'O');
}


unsigned int Board::index(unsigned int col, unsigned int row) const {
    return 3 * (col - 1) + row - 1;
}

void Board::placeAt(unsigned int col, unsigned int row) {
    if (!isValidMove(col, row)){
        throw BoardException(MOVE_INVAL, col, row);
    }
    rawBoard.at(index(col, row)) = currentSymbol;
    bv.updateAt(col, row, currentSymbol);
    aWinner = checkWon();
    updateSymbol();
}

unsigned char Board::checkWon() {
    // primero, verticalmente
    for (size_t c = 1; c <= 3; ++c){
        if (rawBoard.at(index(c, 1)) == currentSymbol &&
            currentSymbol == rawBoard.at(index(c, 2)) &&
            currentSymbol == rawBoard.at(index(c, 3))){
            return currentSymbol;
        }
    }
    // segundo, horizontalmente
    for (size_t r = 1; r <= 3; ++r){
        if (rawBoard.at(index(1, r)) == currentSymbol &&
            currentSymbol == rawBoard.at(index(2, r)) &&
            currentSymbol == rawBoard.at(index(3, r))){
            return currentSymbol;
        }
    }
    // tercero, diagonal izq a der
    if (rawBoard.at(index(1, 1)) == currentSymbol &&
        currentSymbol == rawBoard.at(index(2, 2)) &&
        currentSymbol == rawBoard.at(index(3, 3))){
        return currentSymbol;
    }
    // cuarto, diagonal der a izq
    if (rawBoard.at(index(3, 1)) == currentSymbol &&
        currentSymbol == rawBoard.at(index(2, 2)) &&
        currentSymbol == rawBoard.at(index(1, 3))){
        return currentSymbol;
    }

    //quinto, check tablero lleno
    if (std::any_of(rawBoard.begin(), rawBoard.end(),
                [](char c){ return !c;})){
        return 'N';
    }

    // si llego aca, empataron
    return 'E';
}

const std::string& Board::print() {
    return bv.print();
}

unsigned char Board::getCurrentPlayer() {
    return currentSymbol;
}

Board::~Board() {
}

Board::Board(Board &&other) noexcept
: bv(std::move(other.bv)), rawBoard(other.rawBoard){
    this->currentSymbol = other.currentSymbol;
    this->aWinner = other.aWinner;
    other.currentSymbol = 'N';
}

Board &Board::operator=(Board &&other) noexcept {
    if (this == &other){
        return *this;
    }
    bv = std::move(other.bv);
    rawBoard = other.rawBoard;
    this->currentSymbol = other.currentSymbol;
    other.currentSymbol = 'N';
    this->aWinner = other.aWinner;
    return *this;
}


unsigned char Board::getWinner() {
    return aWinner;
}
