//
// Created by leogm99 on 21/5/21.
//

#ifndef TP3_SERVER_COMMANDPLAY_H
#define TP3_SERVER_COMMANDPLAY_H

#include <vector>
#include "server_Board.h"

class CommandPlay{
public:
    void operator()(const std::vector<unsigned char>& message, Board& board);
};


#endif //TP3_SERVER_COMMANDPLAY_H
