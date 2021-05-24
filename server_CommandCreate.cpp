//
// Created by leogm99 on 21/5/21.
//

#include "server_CommandCreate.h"

std::string CommandCreate::operator()() {
    /*try{
        //monitor.createGame(game);
    } catch(const std::exception& e){
        throw;
    }*/
    if (!gameName.empty()){
        throw std::exception();
    }
    gameName.assign(msg.begin() + 3, msg.end());
    monitor.createGame(gameName);
    clientSymbol = 'O';
    return std::string();
}
