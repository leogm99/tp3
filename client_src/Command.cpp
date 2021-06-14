#include "Command.h"
#include "../common_src/CommandException.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>


Command::Command()
: validCommands(Command::createMap()){
}

void Command::serializeCommand() {
   actualCommand.clear();
   std::string in;
   std::getline(std::cin, in);
   std::stringstream ss(in);
   std::string stringCommand;

   ss >> stringCommand;
   try{
       uint8_t command = validCommands.at(stringCommand);
       dispatch(command, ss);
   } catch(const std::exception& e){
       throw CommandException(INVAL_COMMAND);
   }
}

void Command::dispatch(uint8_t command, std::stringstream& ss) {
    switch (command) {
        case CREAR:
            create(ss);
            break;
        case LISTAR:
            list();
            break;
        case UNIRSE:
            join(ss);
            break;
        case JUGAR:
            play(ss);
            break;
        default:
            break;
    }
}

void Command::create(std::stringstream& ss) {
    actualCommand.emplace_back(CREAR);
    serializeGameName(ss);
}

void Command::list() {
    actualCommand.emplace_back(LISTAR);
}

void Command::join(std::stringstream& ss) {
    actualCommand.emplace_back(UNIRSE);
    serializeGameName(ss);
}

void Command::play(std::stringstream& ss) {
    actualCommand.emplace_back(JUGAR);
    std::string row;
    std::string col;
    ss >> col;
    ss >> row;
    uint8_t colN = std::stoul(col, nullptr, 0);
    uint8_t rowN = std::stoul(row, nullptr, 0);
    --colN; // required by solution
    --rowN;

    colN <<= 4;
    uint8_t colRow = colN | rowN;
    actualCommand.emplace_back(colRow);
}

Command::~Command() {
}

Command::Command(Command &&other) noexcept
: validCommands(std::move(other.validCommands)),
  actualCommand(std::move(other.actualCommand)){
}

Command &Command::operator=(Command &&other) noexcept {
    if (this == &other){
        return *this;
    }
    validCommands = std::move(other.validCommands);
    actualCommand = std::move(other.actualCommand);

    return *this;
}

std::vector<uint8_t> Command::getCommand() {
    return this->actualCommand;
}

void Command::serializeGameName(std::stringstream &ss) {
    std::string game;
    ss >> game;
    uint16_t gameSize = game.size();
    actualCommand.emplace_back((gameSize >> 8) & 0xff);
    actualCommand.emplace_back((gameSize >> 0) & 0xff);
    std::copy(game.begin(), game.end(), std::back_inserter(actualCommand));
}
