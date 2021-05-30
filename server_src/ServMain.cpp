#include "Listener.h"
#include <string>

int main(int argc, const char* argv[]){
    if (argc != 2){
        return -1;
    }
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
