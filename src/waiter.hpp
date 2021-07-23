#pragma once
#include "fork.hpp"

#include <vector>
#include <mutex>

#include <deque>

class waiter
{
public:
    
    waiter( std::vector<fork> & _forks )
    : m_forks{_forks}
    {
        m_philosopher_request.reserve( _forks.size() );
    };



/*
            0

            0:  t...EEt..EEL
            1: tttEEtt.EEL
            2: ttEttt.EL

*/

    bool forks_take(int index_philosopher, const char * _name)
    {
        std::lock_guard<std::mutex> lock(m_mutex_waiter);

        if( !m_philosopher_request.empty() )
        {
            if( m_philosopher_request.at(0) != index_philosopher )
            {
            }
        }


        if( m_forks.at(index_philosopher).take_fork() )
        {
            if( index_philosopher+1 != m_forks.size() )
            {
                if( m_forks.at(index_philosopher+1).take_fork())
                {
                    remove_from_the_queue(index_philosopher);
                    return true;
                }
            }
            else
            {
                if( m_forks.at(0).take_fork())
                {
                    remove_from_the_queue(index_philosopher);
                    return true;
                }
            }
            m_forks.at(index_philosopher).put_fork();
        }  


        add_to_queue(index_philosopher);
        
        return false;
        
    };

    void forks_put(int i)
    {
        if( i+1 != m_forks.size())
        {
            m_forks.at(i).put_fork();
            m_forks.at(i+1).put_fork();
            return;
        }
        m_forks.at(i).put_fork();
        m_forks.at(0).put_fork();
    };

private:

    void add_to_queue(int index_philosopher)
    {
        if(m_philosopher_request.empty())
        {
            m_philosopher_request.push_back(index_philosopher);
            return;
        }

        if( !is_exists_in_queue(index_philosopher) )
        {
            m_philosopher_request.push_back(index_philosopher);
        }

    };

    bool is_exists_in_queue(int _index_philosopher)
    {
        if( m_philosopher_request.empty() )
        {
            false;
        }
        for(auto element:m_philosopher_request)
        {
            if( element == _index_philosopher)
            {
                return true;
            }
        }
        return false;
    };

    void remove_from_the_queue( int index_philosopher)
    {
        if( !m_philosopher_request.empty()  )
        {
            
        }

    };

    
    std::vector<fork> &m_forks;
    std::mutex m_mutex_waiter;
    std::vector<int> m_philosopher_request;

};