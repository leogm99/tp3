//
// Created by leogm99 on 24/5/21.
//

#include <algorithm>
#include "server_Listener.h"

Listener::Listener(ClientMonitor& clientMonitor, const char* service)
: cliMonitor(clientMonitor) {
    if (listenerSock.bindAndListen(service) < 0){
        throw std::invalid_argument("Could not bind/listen on port");
    }
}

void Listener::run() {
    ServProtocol protocol;
    while (true){
        Socket clientSocket;
        try {
            clientSocket = std::move(listenerSock.accept());
        } catch(const std::invalid_argument& e){
            break;
        }

        //clients.emplace_back(cliMonitor, protocol, std::move(clientSocket));
        //clients.back().start(); // lo guardo y start()
        auto* newCli = new ClientHandler(cliMonitor, protocol, std::move(clientSocket));
        newCli->start();
        clients.push_back(newCli);
        /*auto newEnd = std::remove_if(clients.begin(),
                       clients.end(),
                       [](ClientHandler& cli){
                            return cli.isDead();
                        });
        // si no estan jugando, los limpio
        clients.erase(newEnd, clients.end());*/
    }
    // espero a que todos terminen
    for (auto& cli : clients){
        cli->join();
        delete cli;
    }
}

void Listener::shutdown() {
    listenerSock.shutdown();
}

Listener::~Listener() {
    clients.clear();
}

