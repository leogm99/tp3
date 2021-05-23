//
// Created by leogm99 on 22/5/21.
//

#ifndef TP3_SERVER_CLIENTHANDLER_H
#define TP3_SERVER_CLIENTHANDLER_H
#include "server_Thread.h"
#include "server_ClientMonitor.h"
#include "common_Socket.h"

class ClientHandler : public Thread{
private:
    ClientMonitor& monitor;
    Socket clientSocket;
    std::string game;
    unsigned char symbol;
protected:
    void run() override;
public:
    ClientHandler(ClientMonitor& aMonitor, Socket clientSocket);
    ~ClientHandler() override;
};


#endif //TP3_SERVER_CLIENTHANDLER_H
