#include "server_game.h"
#include <functional>
#include <iostream>
#include <algorithm>

Game::Game(std::string number): n(number), intents(10),
 winner(false), loser(false){}

Game::~Game(){}


int Game::check_good(std::string& number){
    int count =0;
    if (number[0] == n[0])count++;
    if (number[1] == n[1])count++;
    if (number[2] == n[2])count++;

    return count;
}

int Game::check_regular(std::string& number){
    int count =0;
    for (int i =0; i <(int)number.size(); i++){
        if (std::find(n.begin(), n.end(),number[i]) != n.end()) 
            count++;
    }
    return count;
}

bool Game::is_winner(){
    return winner;
}

void Game::win_game(){
    winner = true;
}

bool Game::is_loser(){
    return loser;
}

void Game::loose_game(){
    loser = true;
}

void Game::spend_intent(){
    intents--;
}

bool Game::has_intents(){
    return intents > 0;
}
