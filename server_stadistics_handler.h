#ifndef STADISTICS_HANDLER
#define STADISTICS_HANDLER
#include <atomic>

class StadisticsHandler{
private:
    std::atomic<int> winners;
    std::atomic<int> losers;
public:
    StadisticsHandler();
    ~StadisticsHandler();
    void increment_winners();
    void increment_losers();
    void operator()();
};

#endif
