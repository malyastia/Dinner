#pragma once
#include "fork.hpp"

#include <vector>
#include <mutex>

class waiter
{
public:
    
    waiter( std::vector<fork> & _forks )
    : m_forks{_forks}
    {};

    bool forks_take(int i, const char * _name)
    {
        std::lock_guard<std::mutex> lock(m_mutex_waiter);

        // log.startActivity(ActivityType::failed_in_queue);
            // if( m_fork_request_queue.front() < m_forks.size() && m_fork_request_queue.front() > 0)
            // {
            //     if( m_fork_request_queue.front() == i-1 || m_fork_request_queue.front() == i+1 )
            //     {
            //         log.startActivity(ActivityType::failed_in_queue);
            //         m_fork_request_queue.push(i);
            //         return false;
            //     }
            // }

            // if( m_fork_request_queue.front() == 0)
            // {
            //     if( m_fork_request_queue.front() == m_forks.size()-1 || m_fork_request_queue.front() == 0 )
            //     {
            //         log.startActivity(ActivityType::failed_in_queue);
            //         m_fork_request_queue.push(i);
            //         return false;
            //     }
            // }
            // if( m_fork_request_queue.front() + 1 == m_forks.size())
            // {
            //     if( m_fork_request_queue.front() == i-1 || m_fork_request_queue.front() == m_forks.size()-1 )
            //     {
            //         log.startActivity(ActivityType::failed_in_queue);
            //         m_fork_request_queue.push(i);
            //         return false;
            //     }
            // }


        if( m_forks.at(i).take_fork() )
        {
            if( i+1 != m_forks.size() )
            {
                if( m_forks.at(i+1).take_fork())
                {
                    return true;
                }
                m_forks.at(i).put_fork();
                return false;
            }
            else
            {
                if( m_forks.at(0).take_fork())
                {
                    return true;
                }
            }
            m_forks.at(i).put_fork();
            return false;
            
        }
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
    std::vector<fork> &m_forks;
    std::mutex m_mutex_waiter;
};