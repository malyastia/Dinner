#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "library.hpp"
#include "fork.hpp"
#include "philosopher.hpp"

#include "waiter.hpp"
#include "waiter_with_queue.hpp"

namespace dinner_desk{
    

void dining( int eat_count)
{
    const size_t count_philosopher = 6;
    std::vector<dinner::fork> forks{count_philosopher};

    dinner::start_eating_philosopher for_start_eating_philosopher;

    // dinner::waiter local_waiter{forks};
    dinner::waiter_with_queue local_waiter{forks};

   
    dinner::philosopher::philosopher_setting philosoph0 {0, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(25), std::chrono::milliseconds(5), eat_count};
    dinner::philosopher::philosopher_setting philosoph1 {1, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(10), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher::philosopher_setting philosoph2 {2, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher::philosopher_setting philosoph3 {3, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher::philosopher_setting philosoph4 {4, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher::philosopher_setting philosoph5 {5, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};

    std::array<dinner::philosopher, count_philosopher> philosophers
    {
        {        
            {philosoph0},
            {philosoph1},
            {philosoph2}, 
            {philosoph3}, 
            {philosoph4},  
            {philosoph5}
        }        
    };



    

    for_start_eating_philosopher.start();        
    for(auto &ph:philosophers){
            ph.joining_thread() ;
    } 

    for(auto &ph:philosophers){
        ph.eventLog().printSummary();
    } 
    
}

} //dinner_desk


int main()
{
    int eat_count = 5;
    dinner_desk::dining( eat_count);
    
    return 0;
}