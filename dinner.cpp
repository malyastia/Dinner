#include "lib/library.hpp"
#include "philosopher_and_fork/fork.hpp"
#include "philosopher_and_fork/philosopher.hpp"

#include "waiter/waiter_without_queue.hpp"
#include "waiter/waiter_with_queue.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

namespace dinner_desk{
    

void dining( int eat_count)
{
    const size_t count_philosopher = 6;
    std::vector<dinner::fork> forks{count_philosopher};

/*     dinner::waiter_without_queue local_waiter{forks};
   
    dinner::philosopher_setting<dinner::waiter_without_queue> philosoph0 {0, local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(25), std::chrono::milliseconds(5), eat_count};
    dinner::philosopher_setting<dinner::waiter_without_queue> philosoph1 {1, local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(10), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher_setting<dinner::waiter_without_queue> philosoph2 {2, local_waiter, std::chrono::milliseconds(5), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher_setting<dinner::waiter_without_queue> philosoph3 {3, local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher_setting<dinner::waiter_without_queue> philosoph4 {4, local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};
    dinner::philosopher_setting<dinner::waiter_without_queue> philosoph5 {5, local_waiter, std::chrono::milliseconds(10), std::chrono::milliseconds(25), std::chrono::milliseconds(5),eat_count};

    std::array<dinner::philosopher<dinner::waiter_without_queue>, count_philosopher> philosophers
    {
        {        
            {philosoph0},
            {philosoph1},
            {philosoph2}, 
            {philosoph3}, 
            {philosoph4},  
            {philosoph5}, 
        }        
    }; */


    dinner::waiter_with_queue local_waiter{forks};

    dinner::philosopher_setting<dinner::waiter_with_queue> philosoph0 {0, local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(5), std::chrono::milliseconds(15),eat_count};
    dinner::philosopher_setting<dinner::waiter_with_queue> philosoph1 {1, local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(5), std::chrono::milliseconds(15),eat_count};
    dinner::philosopher_setting<dinner::waiter_with_queue> philosoph2 {2, local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(5), std::chrono::milliseconds(15),eat_count};
    dinner::philosopher_setting<dinner::waiter_with_queue> philosoph3 {3, local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(5), std::chrono::milliseconds(15),eat_count};
    dinner::philosopher_setting<dinner::waiter_with_queue> philosoph4 {4, local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(5), std::chrono::milliseconds(15),eat_count};
    dinner::philosopher_setting<dinner::waiter_with_queue> philosoph5 {5, local_waiter, std::chrono::milliseconds(15), std::chrono::milliseconds(5), std::chrono::milliseconds(15),eat_count};

    std::array<dinner::philosopher<dinner::waiter_with_queue>, count_philosopher> philosophers
    {
        {        
            {philosoph0},
            {philosoph1}, 
            {philosoph2}, 
            {philosoph3}, 
            {philosoph4},  
            {philosoph5}, 
        }        
    };

    
    dinner::ready = true;        
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