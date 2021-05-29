//
// Created by leogm99 on 22/5/21.
//

#ifndef TP3_SERVER_CLIENTHANDLER_H
#define TP3_SERVER_CLIENTHANDLER_H

#include <atomic>
#include "server_Thread.h"
#include "server_ClientMonitor.h"
#include "common_Socket.h"
#include "server_Protocol.h"

class ClientHandler : public Thread{
private:
    ClientMonitor& monitor;
    ServProtocol& servProtocol;
    Socket clientSocket;
    std::string game;
    unsigned char symbol;
    std::atomic_bool dead;
    std::atomic_bool playing;
    std::mutex clientMutex;
protected:
    void run() override;
public:
    ClientHandler(ClientMonitor& aMonitor, ServProtocol& protocol, Socket clientSocket);

    ClientHandler(const ClientHandler& other) = delete;
    ClientHandler& operator=(const ClientHandler& other) = delete;

    ClientHandler(ClientHandler&& other) noexcept;
    ClientHandler& operator=(ClientHandler&& other) noexcept;

    void killIfIdle();
    bool isDead();
    ~ClientHandler() override;
};


#endif //TP3_SERVER_CLIENTHANDLER_H
