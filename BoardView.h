//
// Created by leogm99 on 19/5/21.
//

#ifndef TP3_BOARDVIEW_H
#define TP3_BOARDVIEW_H

#include "BoardFileHandler.h"
#include <iostream>
#include <string>

class BoardView {
private:
    std::string boardView;
    const BoardFileHandler& fh;
public:
    explicit BoardView(const BoardFileHandler& fh);

    BoardView(const BoardView& other) = delete;
    BoardView& operator=(const BoardView& other) = delete;

    BoardView(BoardView&& other) noexcept;
    BoardView& operator=(BoardView&& other) noexcept;

    void updateAt(unsigned int col, unsigned int row, char symbol);
    void print();
};

#endif //TP3_BOARDVIEW_H
