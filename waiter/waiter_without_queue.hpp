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
    {}

    unique_take forks_take(int index_philosopher) 
    {
        return unique_take{  &m_forks[index_philosopher],  &m_forks[ ( index_philosopher + 1) % m_forks.size()] };
    }

private:

    int index_next(int index)
    {
        return ((index + 1) % m_forks.size());
    }

    std::vector<fork> &m_forks;
};

} //namespace dinner