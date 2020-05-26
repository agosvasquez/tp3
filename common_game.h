#ifndef GAME
#define GAME
#include "common_file.h"
#include <atomic>
#include <vector>

class Game
{
private:
    File file;
    std::atomic<int> intents;
public:
    Game(std::string file_name);
    ~Game();
    int get_secret_number();
    int check_good_d(int digits, int number);
    int check_regular_d(std::vector<int>& digits, int number);
    void to_vect(int number, std::vector<int>& digits);
};

#endif 
