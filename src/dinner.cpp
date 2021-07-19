#include "eventLog.hpp"
#include "fork.hpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

template<typename _iterator>
void dinner(_iterator begin_iteraton_philosopher, _iterator end_iteraton_philosopher)
{
    
    std::thread threads[4];
    int i = 0;
    
    _iterator it = begin_iteraton_philosopher;
    {
        
        for ( i = 0 ; i < 4 ; ++i)
        {
            threads[i] = std::thread( &philosopher::work, it);
            ++it;
        }  
        
        ready = true;
    }

    {
        for ( i =0 ; i < 4 ; ++i)
        {
            threads[i].join();
        }  
    }

    std::cout << "Dinner started!" << std::endl;
    
    {
        _iterator it = begin_iteraton_philosopher;
        for( ; it != end_iteraton_philosopher; ++it )
        {
            it->eventLog().printSummary();
        }
    }
    

    std::cout << "Dinner done!" << std::endl;
    
}


int main()
{

    const size_t eat_count = 4;
    fork forks;
    const size_t count_food = 4;
    std::array<philosopher, eat_count> philosophers
    {
        {
            {"0", 10, 30, count_food},
            {"1", 20, 10, count_food},
            {"2", 10, 10, count_food},
            {"3", 20, 30, count_food}
        }
    };


    dinner(std::begin(philosophers), std::begin(philosophers)+4 );
    
    return 0;
}