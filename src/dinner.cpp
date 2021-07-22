#include "eventLog.hpp"
#include "fork.hpp"
#include "philosopher.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

const size_t count_philosopher = 5;
void dinner(int eat_count)
{
    std::vector<fork> forks{count_philosopher};

    waiter local_waiter{forks};

    std::array<philosopher, count_philosopher> philosophers
    {
        {
            {0, "0", local_waiter, 5, 10, eat_count},
            {1, "1", local_waiter, 5, 10, eat_count},
            {2, "2", local_waiter, 5, 10, eat_count},
            {3, "3", local_waiter, 5, 5, eat_count},
            {4, "4", local_waiter, 5, 10, eat_count}
        }
    };
    

    std::cout << "Dinner started!" << std::endl;
    
    {
        ready = true;
    };
    {
        bool done;
        do {
            done = true;
            for (auto& ph : philosophers)
            {
                // std::cout << ph.isDone();
                done = done && ph.isDone();
            };
            // std::cout << std::endl;
            
        } while (!done);
    }
    
    
        std::cout << "Dinner done!" << std::endl;
        for(auto &ph:philosophers){
            ph.eventLog().printSummary();
        }
    
    
}

int main()
{
    const int eat_count = 2;
    dinner( eat_count);
    
    return 0;
}