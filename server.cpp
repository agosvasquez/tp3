#include <iostream>
#include "server_acceptor.h"
#include <string>

namespace{
    std::string QUIT = "q";
}

int main(int argc, char *argv[]) {
     if (argc < 3) {
        std::cout<< "Error: argumentos invalidos." << std::endl;
        return 1;
    }
    try{
        std::string line;
        char* port = argv[1];
        std::string file_name= argv[2];
        
        Acceptor acceptor(port, file_name);
        acceptor.start();

        while (std::cin >> line)
            if (line == QUIT){acceptor.stop(); break;}
        
        acceptor.join();
    }catch(const std::exception& e){
        printf("%s", e.what());
        return 0;
    }catch(...){
        printf("Unknown error");
        return 0;
    }
}
