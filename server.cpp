#include <iostream>
#include "server_acceptor.h"
#include <string>

namespace{
    std::string QUIT = "q";
}

int main(int argc, char *argv[]) {
     if (argc < 3) {
        std::cout<< "Uso: ./server <puerto> <numeros>" << std::endl;
        return 1;
    }
    std::string line;
    char* port = argv[1];
    std::string file_name= argv[2];
    
    Acceptor acceptor(port, file_name);

    acceptor.start();

	while(std::cin >> line)
		if (line == QUIT){acceptor.stop(); break;}
	
    std::cout<< "join" << std::endl;
    acceptor.join();


    return 0;
}