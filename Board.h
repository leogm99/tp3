//
// Created by leogm99 on 19/5/21.
//

#ifndef TP3_BOARD_H
#define TP3_BOARD_H
#include "BoardView.h"
#include <array>

class Board {
private:
    std::array<char, 9> rawBoard{0};
    char currentSymbol;
    BoardView bv;
    bool isOccupied(unsigned int col, unsigned int row) const;
    bool isValidMove(unsigned int col, unsigned int row) const;
    void updateSymbol();
    unsigned int index(unsigned int col, unsigned int row) const;
public:
    explicit Board(BoardView bv);

    Board(const Board& other) = delete;
    Board& operator=(const Board& other) = delete;

    void placeAt(unsigned int col, unsigned int row);
    char checkWon();
    void print();

    ~Board();
};


#endif //TP3_BOARD_H