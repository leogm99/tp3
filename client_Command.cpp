//
// Created by leogm99 on 20/5/21.
//

#include "client_Command.h"
#include <iostream>
#include <sstream>

Command::Command() {
    // el de este namespace por favorcito
    validCommands = std::move(Command::createMap());
}

void Command::serializeCommand() {
   actualCommand.clear();
   std::string in;
   std::getline(std::cin, in);
   std::stringstream ss(in);
   std::string stringCommand;

   ss >> stringCommand;
   uint8_t command;
   try{
       command = validCommands.at(stringCommand);
       dispatch(command, ss);
   } catch(const std::exception& e){
       throw e;
   }
}

void Command::dispatch(uint8_t command, std::stringstream& ss) {
    switch(command) {
        case crear:
            create(ss);
            break;
        case listar:
            list();
            break;
        case unirse:
            join(ss);
            break;
        case jugar:
            play(ss);
            break;
        default:
            break;
    }
}

void Command::create(std::stringstream& ss) {
    actualCommand.emplace_back(crear);
    std::string game;
    ss >> game;
    uint16_t gameSize = game.size();
    actualCommand.emplace_back((gameSize >> 8) & 0xff);
    actualCommand.emplace_back((gameSize >> 0) & 0xff);
    std::copy(game.begin(), game.end(), std::back_inserter(actualCommand));
}

void Command::list() {
    actualCommand.emplace_back(listar);
}

void Command::join(std::stringstream& ss) {
    actualCommand.emplace_back(unirse);
    std::string game;
    ss >> game;
    uint16_t gameSize = game.size();
    actualCommand.emplace_back((gameSize >> 8) & 0xff);
    actualCommand.emplace_back((gameSize >> 0) & 0xff);
    std::copy(game.begin(), game.end(), std::back_inserter(actualCommand));
}

void Command::play(std::stringstream& ss) {
    actualCommand.emplace_back(jugar);
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
: actualCommand(std::move(other.actualCommand)){
}

Command &Command::operator=(Command &&other) noexcept {
    actualCommand = std::move(other.actualCommand);
    return *this;
}

std::vector<uint8_t> Command::getCommand() {
    return this->actualCommand;
}
