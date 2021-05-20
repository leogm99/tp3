//
// Created by leogm99 on 19/5/21.
//

#ifndef TP3_BOARDFILEHANDLER_H
#define TP3_BOARDFILEHANDLER_H

#include "BoardException.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>

/*
     (c, f)
0x24 (1, 1) 0x2c
0x44 (1, 2) 0x4c
0x64 (1, 3) 0x6c

*/

class BoardFileHandler {
private:
    std::string plainBoard;

    static std::map<std::pair<unsigned int, unsigned int>,
            unsigned int> createMap(){
        std::map<std::pair<unsigned int, unsigned int>,
                           unsigned int> mapping;
        mapping[std::make_pair(1, 1)] = 0x24;
        mapping[std::make_pair(1, 2)] = 0x44;
        mapping[std::make_pair(1, 3)] = 0x64;
        mapping[std::make_pair(2, 1)] = 0x28;
        mapping[std::make_pair(2, 2)] = 0x48;
        mapping[std::make_pair(2, 3)] = 0x68;
        mapping[std::make_pair(3, 1)] = 0x2c;
        mapping[std::make_pair(3, 2)] = 0x4c;
        mapping[std::make_pair(3, 3)] = 0x6c;
        return mapping;
    }
    std::map<std::pair<unsigned int, unsigned int>, unsigned int> boardMapping;

public:
    explicit BoardFileHandler(const char* boardFile);

    BoardFileHandler(const BoardFileHandler& other) = delete;
    BoardFileHandler& operator=(const BoardFileHandler& other) = delete;

    BoardFileHandler(BoardFileHandler&& other) noexcept;
    BoardFileHandler& operator=(BoardFileHandler&& other) noexcept;

    std::string getPlainBoard() const;
    unsigned int getMapping(unsigned int col, unsigned row) const;

    ~BoardFileHandler();
};


#endif //TP3_BOARDFILEHANDLER_H
