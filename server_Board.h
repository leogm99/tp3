#ifndef TP3_SERVER_BOARD_H
#define TP3_SERVER_BOARD_H
#include "server_BoardView.h"
#include <array>
#include <string>

class Board {
private:
    BoardView bv;
    std::array<char, 9> rawBoard;
    char currentSymbol;
    unsigned char aWinner;
    void updateSymbol();
    bool isOccupied(unsigned int col, unsigned int row) const;
    bool isValidMove(unsigned int col, unsigned int row) const;
    unsigned int index(unsigned int col, unsigned int row) const;

public:
    explicit Board(BoardView bv);

    Board(const Board& other) = delete;
    Board& operator=(const Board& other) = delete;

    Board(Board&& other) noexcept;
    Board& operator=(Board&& other) noexcept;

    void placeAt(unsigned int col, unsigned int row);
    unsigned char checkWon();
    const std::string& print();

    unsigned char getWinner();
    unsigned char getCurrentPlayer();

    ~Board();
};


#endif //TP3_SERVER_BOARD_H
