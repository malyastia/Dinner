#include "eventLog.hpp"
#include "fork.hpp"
#include "philosopher.hpp"

#include "protocol.hpp"
#include "waiter.hpp"
#include "waiter_with_queue.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

const size_t count_philosopher = 5;
void dinner(int eat_count)
{
    std::vector<fork> forks{count_philosopher};

    // waiter local_waiter{forks};
    waiter_with_queue local_waiter{forks};

    std::array<philosopher, count_philosopher> philosophers
    {
        {
            {0, "0", local_waiter, 5, 10, eat_count},
            {1, "1", local_waiter, 10, 5, eat_count},
            {2, "2", local_waiter, 10, 15, eat_count},
            {3, "3", local_waiter, 5, 5, eat_count},
            {4, "4", local_waiter, 15, 15, eat_count}
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
                done = done && ph.isDone();
            };
            
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