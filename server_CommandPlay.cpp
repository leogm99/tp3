//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandPlay.h"

void CommandPlay::operator()(const std::vector<unsigned char> &message, Board& board) {
    unsigned char colRow = message.at(1); // el byte de col/fila
    unsigned char col = ((colRow & 0xf0) >> 4) + 1; // esta en los 4 bits mas altos
    unsigned char row = (colRow & 0xf) + 1; // 4 bits mas bajos, sumo 1 pq el protocolo lo manda indexado en 0
    board.placeAt(col, row);
}