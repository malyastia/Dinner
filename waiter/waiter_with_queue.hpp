#pragma once
#include "../philosopher_and_fork/fork.hpp"

#include "unique_take.hpp"

#include <vector>
#include <mutex>

#include "stdio.h"

namespace dinner{

class waiter_with_queue 
{
public:
    
    waiter_with_queue( std::vector<fork> & _forks )
    : m_forks(_forks)
    , m_philosopher_request(_forks.size())
    {};

    unique_take forks_take(int index_philosopher) 
    {    

        if( is_more_than_neighbors(index_philosopher) ) 
        {
            return  std::move(unique_take{}); 
        } 
        
        unique_take take_two_forks{  &m_forks[index_philosopher],  &m_forks[ ( index_philosopher + 1) % m_forks.size()] };
        if(take_two_forks)
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
        }   
        return std::move(take_two_forks); 
             
    }


    bool is_more_than_neighbors(int index_philosopher)
    {    
        if( index_philosopher!=0)
        {
            if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire) || 
              m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[(index_philosopher-1)% m_forks.size() ].load(std::memory_order_acquire) ) 
            {
                return true;
            }
        }
        else
        {
            if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire) || 
                  m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[ m_forks.size()-1 ].load(std::memory_order_acquire) ) 
            {
                return true;
            }
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