#pragma once
#include "../philosopher_and_fork/fork.hpp"
#include "waiter.hpp"

#include <vector>
#include <mutex>

#include <algorithm>

namespace dinner{

class waiter_without_queue 
{
public:
    
    waiter_without_queue( std::vector<fork> & _forks )
    : m_forks{_forks}
    // , waiter{_forks}
    {};


    virtual bool forks_take(int index_philosopher) 
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

    void forks_put(int index_philosopher) 
    {
        if( index_philosopher+1 != m_forks.size())
        {
            m_forks.at(index_philosopher).put_fork();
            m_forks.at(index_philosopher+1).put_fork();
            return;
        }
        m_forks.at(index_philosopher).put_fork();
        m_forks.at(0).put_fork();
    };

private:

    std::vector<fork> &m_forks;

};

}; //namespace dinner