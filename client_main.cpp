#include <iostream>
#include <functional>
#include "client_proxy.h"
#include <fstream>


int main(int argc, char *argv[]) {
    char* host = argv[1];
    char* service = argv[2];
    
    try{
        ClientProxy client_proxy;
        std::string line;

        client_proxy.connect(host,service);
        while (getline(std::cin, line))
            client_proxy.run(std::ref(line));
    }catch(const std::exception& e){ 
        return 0;
    }catch(...){
        printf("Unknown error");
        return 0;
    }
}
