#pragma once
#include "../philosopher_and_fork/fork.hpp"
#include "waiter_without_queue.hpp"

#include <vector>
#include <mutex>

#include <algorithm>

namespace dinner{

// template<size_t count_philosopher>
class waiter_with_queue : public waiter_without_queue
{
public:
    
    waiter_with_queue( std::vector<fork> & _forks )
    : m_forks{_forks}
    , waiter_without_queue{_forks}
    , m_philosopher_request(_forks.size())
    {
        for(auto & el: m_philosopher_request)
        {
            el.store(0, std::memory_order_release);
        };
    };

    bool forks_take(int index_philosopher) 
    {
        if( index_philosopher == 0 
            && ( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[index_philosopher+1].load(std::memory_order_acquire) 
            || m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[m_forks.size() -1].load(std::memory_order_acquire) ) )
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
            return false;
        
        }

        if( index_philosopher == m_forks.size()-1 
            && ( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[index_philosopher-1].load(std::memory_order_acquire) 
            || m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[0].load(std::memory_order_acquire) ) )
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
            return false;
            
        }

        if( index_philosopher != 0 && index_philosopher != m_forks.size()-1 
            && ( m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[index_philosopher+1].load(std::memory_order_acquire) 
            || m_philosopher_request[index_philosopher].load(std::memory_order_acquire) < m_philosopher_request[index_philosopher-1].load(std::memory_order_acquire) ) )
        {
            m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
            return false;
            
        }

        if( m_forks[index_philosopher].take_fork())
        {
            if( index_philosopher+1 != m_forks.size() && m_forks[index_philosopher+1].take_fork())
            {
                m_philosopher_request[index_philosopher].store(0,std::memory_order_release);
                
                return true;
                
            }
            
            if( index_philosopher+1 == m_forks.size() && m_forks[0].take_fork())
            {
                m_philosopher_request[index_philosopher].store(0,std::memory_order_release);
                return true;
            }

            m_forks[index_philosopher].put_fork();
        }
        
        
        m_philosopher_request[index_philosopher].fetch_add(1,std::memory_order_release);
                    
        return false;

    }


    

private:

    std::vector<fork> &m_forks;
    std::vector<std::atomic_int> m_philosopher_request;

};
}; // namespace dinner

/*





*/