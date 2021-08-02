#pragma once
#include "../philosopher_and fork/fork.hpp"
#include "waiter.hpp"

#include <vector>
#include <mutex>

#include <algorithm>

namespace waiter_solution{

class waiter_without_queue : public waiter
{
public:
    
    waiter_without_queue( std::vector<fork::fork> & _forks )
    : m_forks{_forks}
    , waiter{_forks}
    {};

    

private:
    bool can_take_fork(int index_philosopher)
    {

        if( m_forks.at(index_philosopher).take_fork() )
        {
            if( index_philosopher+1 != m_forks.size() )
            {
                if( m_forks.at(index_philosopher+1).take_fork())
                {
                    return true;
                }
            }
            else
            {
                if( m_forks.at(0).take_fork())
                {
                    return true;
                }
            }
            m_forks.at(index_philosopher).put_fork();
        }  

        return false;
        
    };

    std::vector<fork::fork> &m_forks;
    std::mutex m_mutex_waiter;

};

}; //namespace waiter_solution