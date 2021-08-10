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

        if( !condition_true(index_philosopher) ) 
        {
            printf("index %d - %d - %d - %d \n", index_philosopher ,
            m_philosopher_request[(index_philosopher-1)% m_forks.size() ].load(std::memory_order_acquire),
            m_philosopher_request[index_philosopher].load(std::memory_order_acquire),
            m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire) );
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release) ;
            
            unique_take take_two_forks;
            return take_two_forks;  
            
        }

        unique_take take_two_forks{  &m_forks[index_philosopher],  &m_forks[ ( index_philosopher + 1) % m_forks.size()] };
        if(take_two_forks)
        {
            printf("\n\t URAAA %d - %d - %d - %d ==%ld ==%ld \n", index_philosopher ,
            m_philosopher_request[(index_philosopher-1)% m_forks.size() ].load(std::memory_order_acquire),
            m_philosopher_request[index_philosopher].load(std::memory_order_acquire),
            m_philosopher_request[(index_philosopher+1) % m_forks.size() ].load(std::memory_order_acquire),
            index_philosopher!=0 ? (index_philosopher-1) % m_forks.size(): m_forks.size()-1 ,(index_philosopher+1)% m_forks.size() );


            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
        }

        return take_two_forks;
    }


    bool condition_true (int index_philosopher)
    {    
        if( index_philosopher!=0)
        {if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire) || 
            (  m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[(index_philosopher-1)% m_forks.size() ].load(std::memory_order_acquire)) ) 
        {
            printf("\n QQQQQQQQQQQQQQQQ %d - %d - %d - %d ==%ld ==%ld \n", index_philosopher ,
            m_philosopher_request[(index_philosopher-1)% m_forks.size() ].load(std::memory_order_acquire),
            m_philosopher_request[index_philosopher].load(std::memory_order_acquire),
            m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire),
            (index_philosopher-1)% m_forks.size(),(index_philosopher+1)% m_forks.size() );

            return true;
        
        }
        }

        else
        if( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire) || 
            (  m_philosopher_request[index_philosopher].load(std::memory_order_acquire) > m_philosopher_request[ m_forks.size()-1 ].load(std::memory_order_acquire) )) 
        {
            printf("\n AAAAAAAAAAAAAA %d - %d - %d - %d ==%ld ==%ld \n", index_philosopher ,
            m_philosopher_request[(index_philosopher-1)% m_forks.size() ].load(std::memory_order_acquire),
            m_philosopher_request[index_philosopher].load(std::memory_order_acquire),
            m_philosopher_request[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acquire),
            m_forks.size()-1 ,  (index_philosopher+1)% m_forks.size() );

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