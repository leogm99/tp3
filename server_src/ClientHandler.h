#ifndef TP3_SERVER_CLIENTHANDLER_H
#define TP3_SERVER_CLIENTHANDLER_H

#include <atomic>
#include <string>
#include "Thread.h"
#include "ClientMonitor.h"
#include "../common_src/Socket.h"
#include "ServProtocol.h"

class ClientHandler : public Thread{
private:
    ClientMonitor& monitor;
    ServProtocol& servProtocol;
    Socket clientSocket;
    std::string game;
    unsigned char symbol;
    std::atomic_bool dead;
    std::atomic_bool playing;

protected:
    void run() override;

public:
    ClientHandler(ClientMonitor& aMonitor,
                  ServProtocol& protocol,
                  Socket clientSocket);

    ClientHandler(const ClientHandler& other) = delete;
    ClientHandler& operator=(const ClientHandler& other) = delete;

    ClientHandler(ClientHandler&& other) noexcept;
    ClientHandler& operator=(ClientHandler&& other) noexcept;

    void killIfIdle();
    bool isDead();
    ~ClientHandler() override;
};


#endif //TP3_SERVER_CLIENTHANDLER_H
