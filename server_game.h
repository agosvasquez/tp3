#ifndef GAME
#define GAME
#include <atomic>
#include <string>

class Game{
private:
    std::string n;
    std::atomic<int> intents;
    bool winner;
    bool loser;
public:
    explicit Game(std::string number);
    ~Game();
    int check_good(std::string& number);
    int check_regular(std::string& number);
    bool is_winner();
    void win_game();
    bool is_loser();
    void loose_game();
    void spend_intent();
    bool has_intents();
};

#endif 

