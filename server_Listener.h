//
// Created by leogm99 on 24/5/21.
//

#ifndef TP3_SERVER_LISTENER_H
#define TP3_SERVER_LISTENER_H

#include <vector>
#include "server_Thread.h"
#include "common_Socket.h"
#include "server_ClientHandler.h"
#include "server_ClientMonitor.h"

class Listener : public Thread {
private:
    ClientMonitor& cliMonitor;
    Socket listenerSock;
    std::vector<ClientHandler*> clients;
protected:
    void run() override;
public:
    explicit Listener(ClientMonitor& clientMonitor, const char* service);

    void shutdown();

    ~Listener() override;
};


#endif //TP3_SERVER_LISTENER_H
