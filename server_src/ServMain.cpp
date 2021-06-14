#include "Listener.h"
#include <string>

int main(int argc, const char* argv[]){
    if (argc != 2){
        return -1;
    }
    std::string in;
    try {
        ClientMonitor clientMonitor;
        Listener l(clientMonitor, argv[1]);
        l.start();
        while (in != "q"){
            std::cin >> in;
        }
        l.shutdown();
        l.join();
    } catch(const std::exception& e){
        std::cout << e.what();
        return -1;
    }
    return 0;
}
