#include "server_stadistics_handler.h"
#include <iostream>

StadisticsHandler::StadisticsHandler():winners(0), losers(0){}

StadisticsHandler::~StadisticsHandler(){}

void StadisticsHandler::increment_losers(){
    losers++;
}

void StadisticsHandler::increment_winners(){
    winners++;
}

void StadisticsHandler::operator()(){
    std::cout << "Estadísticas:\n\tGanadores:  "<< winners;
    std::cout <<"\n\tPerdedores: "<<losers << "\n";
}
