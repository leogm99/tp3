#ifndef TP3_SERVER_BOARDVIEW_H
#define TP3_SERVER_BOARDVIEW_H

#include <iostream>
#include <string>
#include <utility>
#include <map>

class BoardView {
private:
    std::string boardView;

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

    unsigned int getMapping(unsigned int col,
                            unsigned int row) const;

public:
    BoardView();

    BoardView(const BoardView& other) = delete;
    BoardView& operator=(const BoardView& other) = delete;

    BoardView(BoardView&& other) noexcept;
    BoardView& operator=(BoardView&& other) noexcept;

    void updateAt(unsigned int col, unsigned int row, char symbol);
    const std::string& print();
};

#endif //TP3_SERVER_BOARDVIEW_H
