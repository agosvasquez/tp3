#ifndef SERVER_HELPER
#define SERVER_HELPER
#include <vector>
#include "common_game.h"

class ServerHelper{
private:
    std::vector<int> digits;
    Game& game;
public:
    ServerHelper(Game& game);
    ~ServerHelper();
    std::tuple<int,char*> decode_command(char command,short r,int my_number);
    bool split_in_digits(int num);
    bool verify_digit(int d);
};


#endif
