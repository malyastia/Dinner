#pragma once

#include <vector>
#include <mutex>

#include "fork.hpp"
#include "unique_take.hpp"

namespace dinner{

class waiter
{
public:
    waiter( std::vector<fork> & _forks )
    : m_forks(_forks)
    {}
    
    virtual unique_take forks_take(int index_philosopher) 
    {

        unique_take take_two_forks{  &m_forks[index_philosopher],  &m_forks[ index_next( index_philosopher) ] };

        return take_two_forks;

    }
protected:
    int index_next(int index)
    {
        return ((index + 1) % m_forks.size());
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
private:
    std::vector<fork> &m_forks;

};
} // namespace dinner