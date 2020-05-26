#ifndef CLIENT_ENCODE
#define CLIENT_ENCODE
#include <string>

class ClientEncode{
private:
    
public:
    ClientEncode();
    ~ClientEncode();
     std::tuple<int,char*> get_command_encoded(std::string line);
    bool is_number(std::string& line);
};


#endif