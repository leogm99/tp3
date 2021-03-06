#include <iostream>
#include "Client.h"

int main(int argc, const char* argv[]){
    if (argc != 3){
        return -1;
    }
    try {
        Client client(argv[1], argv[2]);
        client.start();
    } catch(const std::exception& e){
        std::cout << e.what();
    }
    return 0;
}
