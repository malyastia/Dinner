#pragma once
#include "../philosopher_and_fork/fork.hpp"

#include "unique_take.hpp"


#include <vector>
#include <mutex>

#include <algorithm>

namespace dinner{

class waiter_with_queue 
{
public:
    
    waiter_with_queue( std::vector<fork> & _forks )
    : m_forks{_forks}
    , m_philosopher_request(_forks.size())
    {};

    unique_take forks_take(int index_philosopher) 
    {       
        if( condition_true(index_philosopher) )
        {
            return unique_take{};
        };

        
        unique_take take_two_forks{  &m_forks[index_philosopher],  &m_forks[ ( index_philosopher + 1) % m_forks.size() ] };

        if( take_two_forks )
        {
            m_philosopher_request[index_philosopher].fetch_add( 1,std::memory_order_acq_rel) ;
            
        }
        return take_two_forks; 

        // unique_take empty_unique_take{};
        // return empty_unique_take; 

    }
//если он больше соседей
    bool condition_true (int index_philosopher)
    {        
        if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[ (index_philosopher+1) % m_forks.size() ].load(std::memory_order_acquire) 
            || m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[ (index_philosopher-1) % m_forks.size() ].load(std::memory_order_acquire)  )
        {
            printf( "%d %d %d",m_philosopher_request[ (index_philosopher+1) % m_forks.size() ].load(std::memory_order_acquire),
            m_philosopher_request[index_philosopher].load(std::memory_order_acquire) , m_philosopher_request[ (index_philosopher-1) % m_forks.size() ].load(std::memory_order_acquire) );
            std::cout << "YES" << std::endl;
            return true;
        }        
        
        return false;
    };
    
/* 

    void forks_put(int index_philosopher) 
    {
        
        m_forks[ index_philosopher].put_fork();
        m_forks[ (index_philosopher +1) % m_forks.size()].put_fork();
           
    };  */   

private:

    std::vector<fork> &m_forks;
    std::vector<std::atomic_int> m_philosopher_request;

};
} // namespace dinner
