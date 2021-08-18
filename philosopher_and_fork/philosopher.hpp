#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "library.hpp"
#include "fork.hpp"
#include "philosopher.hpp"dinner::waiter_with_queue local_waiter{forks};

    dinner::philosopher<dindinner::waiter_with_queue local_waiter{forks};

    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph0{0, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph1{1, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph2{2, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph3{3, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph4{4, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph5{5, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};

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
    };ner::waiter_with_queue>::philosopher_setting philosoph0{0, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph1{1, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph2{2, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph3{3, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph4{4, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};
    dinner::philosopher<dinner::waiter_with_queue>::philosopher_setting philosoph5{5, for_start_eating_philosopher, local_waiter, std::chrono::milliseconds(30), std::chrono::milliseconds(50), std::chrono::milliseconds(20), eat_count};

    std::array<dinner::philosopher<dinner::waiter_with_queu