#pragma once

#include <vector>
#include <mutex>

#include "waiter.hpp"
#include "unique_take.hpp"

namespace dinner{

class waiter_with_queue : public waiter
{
public:
    
    waiter_with_queue( std::vector<fork> & _forks )
    : waiter (_forks)
    , m_forks(_forks)
    , m_philosopher_amount_of_food_eaten(_forks.size())
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
            m_philosopher_amount_of_food_eaten[index_philosopher].fetch_add(1,std::memory_order_acq_rel);
        }   
        return std::move(take_two_forks); 
             
    } 

private:
    bool is_more_than_neighbors(int index_philosopher)
    {    
        if( index_philosopher==0 )
        {
            if( m_philosopher_amount_of_food_eaten[index_philosopher].load(std::memory_order_acq_rel) > m_philosopher_amount_of_food_eaten[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acq_rel) || 
                m_philosopher_amount_of_food_eaten[index_philosopher].load(std::memory_order_acq_rel) > m_philosopher_amount_of_food_eaten[ m_forks.size()-1 ].load(std::memory_order_acq_rel) ) 
            {
                return true;
            }
        }
        else
        {
            if( m_philosopher_amount_of_food_eaten[index_philosopher].load(std::memory_order_acq_rel) > m_philosopher_amount_of_food_eaten[(index_philosopher+1)% m_forks.size() ].load(std::memory_order_acq_rel) || 
                m_philosopher_amount_of_food_eaten[index_philosopher].load(std::memory_order_acq_rel) > m_philosopher_amount_of_food_eaten[ (index_philosopher-1)% m_forks.size()  ].load(std::memory_order_acq_rel) ) 
            {
                return true;
            }
        }
        
        return false;
    };

private:
    std::vector<fork> &m_forks;
    std::vector<std::atomic_int> m_philosopher_amount_of_food_eaten;

};
} // namespace dinner