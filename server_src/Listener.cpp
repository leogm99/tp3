#include <utility>
#include <algorithm>
#include "Listener.h"

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
        auto* newCli = new ClientHandler(cliMonitor,
                                         protocol,
                                         std::move(clientSocket));
        newCli->start();
        clients.push_back(newCli);

        auto it = clients.begin();
        while (it != clients.end()){
            if ((*it)->isDead()){
                (*it)->join();
                delete *it;
                it = clients.erase(it);
            } else {
                ++it;
            }
        }
    }

    auto it = clients.begin();
    while (it != clients.end()){
        (*it)->killIfIdle();
        if ((*it)->isDead()){
            (*it)->join();
            delete *it;
            it = clients.erase(it);
        } else {
            ++it;
        }
    }

    // espero a que el resto termine
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

Listener::Listener(Listener &&other) noexcept
: cliMonitor(other.cliMonitor),
  listenerSock(std::move(other.listenerSock)),
  clients(std::move(other.clients)){
}

Listener &Listener::operator=(Listener &&other) noexcept {
    if (this == &other){
        return *this;
    }

    this->listenerSock = std::move(other.listenerSock);
    this->clients = std::move(other.clients);
    return *this;
}

