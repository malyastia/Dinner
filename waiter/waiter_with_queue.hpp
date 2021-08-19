#pragma once

#include <vector>
#include <mutex>

#include "fork.hpp"
#include "unique_take.hpp"

namespace dinner{

class waiter_with_queue 
{
public:
    
    waiter_with_queue( std::vector<fork> & _forks )
    : m_forks(_forks)
    , m_philosopher_amount_of_food_eaten(_forks.size())
    {}

    unique_take forks_take(int index_philosopher) 
    {    

        if( is_more_than_neighbors(index_philosopher) ) 
        {
            return  unique_take{};
        } 
        
        unique_take take_two_forks{  &m_forks[index_philosopher],  &m_forks[ index_next( index_philosopher) ] };
        if(take_two_forks)
        {
            m_philosopher_amount_of_food_eaten[index_philosopher].fetch_add(1,std::memory_order_acq_rel);
        }   
        return take_two_forks; 
             
    } 

private:
    bool is_more_than_neighbors(int index_philosopher)
    {    
       
        if( m_philosopher_amount_of_food_eaten[index_philosopher].load(std::memory_order_acq_rel) > m_philosopher_amount_of_food_eaten[ index_next(index_philosopher) ].load(std::memory_order_acq_rel) || 
            m_philosopher_amount_of_food_eaten[index_philosopher].load(std::memory_order_acq_rel) > m_philosopher_amount_of_food_eaten[ index_previous(index_philosopher) ].load(std::memory_order_acq_rel) ) 
        {
            return true;
        }
        
        return false;
    }
    
    int index_previous(int index)
    {
        if(index == 0)
        {
            return m_forks.size()-1;
        }
        else
        {
            return index-1;
        }
    }

    int index_next(int index)
    {
        return ((index + 1) % m_forks.size());
    }

    std::vector<fork> &m_forks;
    std::vector<std::atomic_int> m_philosopher_amount_of_food_eaten;

};
} // namespace dinner