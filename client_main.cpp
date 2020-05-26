#include <iostream>
#include "client_proxy.h"


int main(int argc, char *argv[]) {
    char* host = argv[1];
    char* service = argv[2];
    
    ClientProxy client_proxy;
    std::string line;

    client_proxy.connect(host,service);
    while(std::cin >> line){
        try{
            client_proxy.run(line);
        }catch(const std::exception& e){
            std::cout << "Finiish"<< std::endl; 
            break;
        }
    }
        

    return 0;
}