//
// Created by leogm99 on 24/5/21.
//

#ifndef TP3_SERVER_LISTENER_H
#define TP3_SERVER_LISTENER_H

#include <vector>
#include "Thread.h"
#include "../common_src/Socket.h"
#include "ClientHandler.h"
#include "ClientMonitor.h"

class Listener : public Thread {
private:
    ClientMonitor& cliMonitor;
    Socket listenerSock;
    std::vector<ClientHandler*> clients;
protected:
    void run() override;
public:
    explicit Listener(ClientMonitor& clientMonitor, const char* service);

    Listener(const Listener& other) = delete;
    Listener& operator=(const Listener& other) = delete;

    Listener(Listener&& other) noexcept;
    Listener& operator=(Listener&& other) noexcept;

    void shutdown();

    ~Listener() override;
};


#endif //TP3_SERVER_LISTENER_H
