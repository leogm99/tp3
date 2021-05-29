#include "server_BoardFileHandler.h"
#include "server_BoardView.h"
#include "server_ClientMonitor.h"
#include "server_Listener.h"
#include <string>

int main(int argc, const char* argv[]){
    std::string in;
    ClientMonitor clientMonitor;
    Listener l(clientMonitor, argv[1]);
    l.start();
    while (in != "q"){
        std::cin >> in;
    }
    l.shutdown();
    l.join();
    return 0;
}
