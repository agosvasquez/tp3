#include "common_game.h"
#include <functional>
#include <iostream>
#include <algorithm>

Game::Game(std::string file_name):file(file_name),intents(10){}

Game::~Game(){}

int Game::get_secret_number(){
    std::string line;
    if(!file.read(std::ref(line))){ 
        file.go_first();
        file.read(std::ref(line));
    }
    std::cout <<"geting numb: " << line << std::endl;
    return (int)std::stoi(line);
}

int Game::check_good_d(int number, int my_number){
    int count =0;
   

    std::string n = std::to_string(my_number);
    std::string m = std::to_string(number);
   
    if(n[0] == m[0])count++;
    if(n[1] == m[1])count++;
    if(n[2] == m[2])count++;

    std::cout<<"count good" << count;

    return count;
}

int Game::check_regular_d(std::vector<int>& d, int number){
    int count =0;
    std::vector<int> my_digits;
    to_vect(number, my_digits);
    for(int i =0; i <(int)d.size(); i++){
        std::cout<<"en game my dig " << my_digits[0]<<" "<<  my_digits[1]<<" "<<  my_digits[2];
        if (std::find(my_digits.begin(), my_digits.end(), d[i]) != my_digits.end()) 
            count++;
    }
    std::cout<<"count reg " << count;
    return count;
}

void Game::to_vect(int number, std::vector<int>& my_digits){
    int n1 = number%10;
    number /= 10;
    int n2 = number%10;
    number /= 10;
    int n3 = number%10;
    my_digits.push_back(n3);
    my_digits.push_back(n2);
    my_digits.push_back(n1);
}