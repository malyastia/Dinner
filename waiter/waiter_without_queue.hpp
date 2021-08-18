#pragma once

#include <vector>
#include <mutex>

#include "fork.hpp"
#include "unique_take.hpp"

namespace dinner{

class waiter_without_queue 
{
public:
    
    waiter_without_queue( std::vector<fork> & _forks )
    : m_forks(_forks)
    {};
        

    unique_take forks_take(int index_philosopher) 
    {

        unique_take take_two_forks{  &m_forks[index_philosopher],  &m_forks[ ( index_philosopher + 1) % m_forks.size()] };

        return take_two_forks;

    };

private:
    std::vector<fork> &m_forks;
};

} //namespace dinner