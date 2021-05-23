//
// Created by leogm99 on 19/5/21.
//

#ifndef TP3_SERVER_BOARD_H
#define TP3_SERVER_BOARD_H
#include "server_BoardView.h"
#include <array>

class Board {
private:
    BoardView bv;
    std::array<char, 9> rawBoard{0};
    char currentSymbol;
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
    const std::string& print();

    unsigned char getCurrentPlayer();

    ~Board();

};


#endif //TP3_SERVER_BOARD_H
