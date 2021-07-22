#include "eventLog.hpp"
#include "fork.hpp"
#include "philosopher.hpp"
#include "waiter.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

const size_t count_philosopher = 5;
void dinner(int eat_count)
{
    fork forks[count_philosopher];
    // waiter local_waiter;

    std::array<philosopher, count_philosopher> philosophers
    {
        {
            {"0", 5, 10, eat_count, forks[0], forks[1]},
            {"1", 5, 10, eat_count, forks[1], forks[2]},
            {"2", 5, 10, eat_count, forks[2], forks[3]},
            {"3", 5, 5, eat_count, forks[3], forks[4]},
            {"4", 5, 10, eat_count, forks[4], forks[0]}
        }
    };
    

    std::cout << "Dinner started!" << std::endl;
    
    {
        ready = true;
        bool done;
        do {
            done = true;
            for (auto& ph : philosophers)
            {
                done = done && ph.isDone();
            }
        } while (!done);
    }
    
    {
        std::cout << "Dinner done!" << std::endl;
        for(auto &ph:philosophers){
            ph.eventLog().printSummary();
        }
    }
    
    
    
}

int main()
{
    const int eat_count = 2;
    dinner( eat_count);
    
    return 0;
}