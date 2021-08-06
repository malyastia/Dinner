#pragma once
#include "../philosopher_and_fork/fork.hpp"
#include "waiter_without_queue.hpp"

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
        if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[ (index_philosopher+1) % m_forks.size() ].load(std::memory_order_acquire) 
            || m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[ (index_philosopher-1) % m_forks.size() ].load(std::memory_order_acquire) ) 
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
            // return unique_take
        }
        
        unique_take take_two_forks{m_forks[index_philosopher], m_forks[ ( index_philosopher + 1) % m_forks.size()]};
        
        if(  ! (take_two_forks.is_succes()) )
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
        }

        return take_two_forks;




/*         if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[ (index_philosopher+1) % m_forks.size() ].load(std::memory_order_acquire) 
            || m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[ (index_philosopher-1) % m_forks.size() ].load(std::memory_order_acquire) ) 
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
            return false;
        }

        if( m_forks[index_philosopher].take_fork() )
        {
           
            if( m_forks[ (index_philosopher + 1) % m_forks.size()].take_fork())
            {
                m_philosopher_request[ index_philosopher].store(0,std::memory_order_release);
                return true;
            }
            m_forks[ index_philosopher].put_fork();
        }  
        
        m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
                    
        return false; */



    }
    


    void forks_put(int index_philosopher) 
    {
        
        m_forks[ index_philosopher].put_fork();
        m_forks[ (index_philosopher +1) % m_forks.size()].put_fork();
           
    };    

private:

    std::vector<fork> &m_forks;
    std::vector<std::atomic_int> m_philosopher_request;

};
} // namespace dinner
