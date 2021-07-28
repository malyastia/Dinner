#include "philosopher/eventLog.hpp"
#include "philosopher/fork.hpp"
#include "philosopher/philosopher.hpp"

#include "waiter/waiter.hpp"
#include "waiter/waiter_without_queue.hpp"
#include "waiter/waiter_with_queue.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

namespace dinner_desk{
    
const size_t count_philosopher = 5;
void dinner(int eat_count)
{
    std::vector<fork> forks{count_philosopher};

    waiter_solution::waiter_without_queue local_waiter{forks};
    // waiter_with_queue local_waiter{forks};

    std::array<philosopher, count_philosopher> philosophers
    {
        {            
            {0, "0", local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(10), eat_count},
            {1, "1", local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(5), eat_count},
            {2, "2", local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(15), eat_count},
            {3, "3", local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(5), eat_count},
            {4, "4", local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(15), eat_count}   
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
}; //dinner_desk


int main()
{
    const int eat_count = 4;
    dinner_desk::dinner( eat_count);
    
    return 0;
}