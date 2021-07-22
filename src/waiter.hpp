#pragma once
#include "fork.hpp"

#include <vector>

template<int _count_philosopher>
class waiter
{
public:
    waiter()
    {
        for (auto i=0; i < _count_philosopher; ++i)
        {
            m_is_free_forks.push_back(true);
        }

    };

    bool forks_free(int i)
    {
        if( i != _count_philosopher)
        {
            if( m_is_free_forks.at(i) && m_is_free_forks.at(i+1) )
            {
                if( m_forks.at(i).take_fork() && m_forks.at(i+1).take_fork())
                {
                    return true;
                }

                if( m_forks.at(i).is_taken() )
                {
                    m_forks.at(i).put_fork();
                }
                if( m_forks.at(i+1).is_taken() )
                {
                    m_forks.at(i+1).put_fork();
                }
                return false;
            }
            
            return false;
            
        }
        if( m_is_free_forks.at(i) && m_is_free_forks.at(0) )
        {
            return true;
        }

        return false;
    };


private:
    std::vector<bool> m_is_free_forks;
    std::array<fork, _count_philosopher> m_forks;

};