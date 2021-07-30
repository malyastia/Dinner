#include "logger/eventLog.hpp"
#include "philosopher_and fork/fork.hpp"
#include "philosopher_and fork/philosopher.hpp"

#include "waiter/waiter.hpp"
#include "waiter/waiter_without_queue.hpp"
#include "waiter/waiter_with_queue.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

namespace dinner_desk{
    
const size_t count_philosopher = 6;
void dinner(int eat_count)
{
    std::vector<fork> forks{count_philosopher};

    // waiter_solution::waiter_without_queue local_waiter{forks};
    waiter_solution::waiter_with_queue local_waiter{forks};

    philosopher_setting philosoph1 {"0", local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), eat_count};

    
    std::array<philosopher, count_philosopher> philosophers
    {
        {        
            {0,philosoph1},
            {1,philosoph1},
            {2,philosoph1}, 
            {3,philosoph1}, 
            {4,philosoph1},  
            {5,philosoph1}, 
        }
        
    };


    
    ready = true;        
    for(auto &ph:philosophers){
            ph.joining_thread() ;
    } 

    for(auto &ph:philosophers){
        ph.eventLog().printSummary();
    }
  
    
}

}; //dinner_desk


int main()
{
    const int eat_count = 5;
    dinner_desk::dinner( eat_count);
    
    return 0;
}