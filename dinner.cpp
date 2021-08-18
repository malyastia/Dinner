#include "library.hpp"
#include "fork.hpp"
#include "philosopher.hpp"

namespace dinner_desk{
   

void dining( int eat_count)
{
    const size_t count_philosopher = 6;
    std::vector<dinner::fork> forks{count_philosopher};

    dinner::start_eating_philosopher for_start_eating_philosopher;

    dinner::waiter_with_queue local_waiter{forks};

    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph0{0, for_start_eating_philosopher, local_waiter}; 
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph1{1, for_start_eating_philosopher, local_waiter};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph2{2, for_start_eating_philosopher, local_waiter};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph3{3, for_start_eating_philosopher, local_waiter};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph4{4, for_start_eating_philosopher, local_waiter};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph5{5, for_start_eating_philosopher, local_waiter};


    philosoph0.m_thinking_time = std::chrono::milliseconds(30);
    philosoph0.m_eating_time = std::chrono::milliseconds(50);
    philosoph0.m_falling_time = std::chrono::milliseconds(25);
    philosoph0.m_count_eat = eat_count;

    philosoph1.m_thinking_time = std::chrono::milliseconds(30);
    philosoph1.m_eating_time = std::chrono::milliseconds(50);
    philosoph1.m_falling_time = std::chrono::milliseconds(25);
    philosoph1.m_count_eat = eat_count;

    philosoph2.m_thinking_time = std::chrono::milliseconds(30);
    philosoph2.m_eating_time = std::chrono::milliseconds(50);
    philosoph2.m_falling_time = std::chrono::milliseconds(25);
    philosoph2.m_count_eat = eat_count;

    philosoph3.m_thinking_time = std::chrono::milliseconds(30);
    philosoph3.m_eating_time = std::chrono::milliseconds(50);
    philosoph3.m_falling_time = std::chrono::milliseconds(25);
    philosoph3.m_count_eat = eat_count;

    philosoph4.m_thinking_time = std::chrono::milliseconds(30);
    philosoph4.m_eating_time = std::chrono::milliseconds(50);
    philosoph4.m_falling_time = std::chrono::milliseconds(25);
    philosoph4.m_count_eat = eat_count;

    philosoph5.m_thinking_time = std::chrono::milliseconds(30);
    philosoph5.m_eating_time = std::chrono::milliseconds(50);
    philosoph5.m_falling_time = std::chrono::milliseconds(25);
    philosoph5.m_count_eat = eat_count;

    std::array<dinner::philosopher<dinner::waiter_with_queue>, count_philosopher> philosophers
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