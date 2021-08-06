#pragma once
#include "../philosopher_and_fork/fork.hpp"

namespace dinner{

class  unique_take
{
public:

    unique_take( fork* _left_fork, fork* _right_fork)
    : m_left_fork(_left_fork)
    , m_right_fork(_right_fork)
    , m_success_take ( false)
    {        
        
        if( m_left_fork->take_fork() )
        {
            if( m_right_fork->take_fork() )
            {
                m_success_take = true;
            }
            else
            {
                m_left_fork->put_fork();
            }
        }
    };

    unique_take()
    : m_left_fork(nullptr)
    , m_right_fork(nullptr)
    , m_success_take ( false)
    {};

    bool is_succes()
    {
        return m_success_take;
    };

    ~unique_take()
    {
        if(m_success_take)
        {
            m_left_fork->put_fork();
            m_right_fork->put_fork();
        }
    };

private:
    fork* m_left_fork;
    fork* m_right_fork;

    bool m_success_take;

};

} // namespace dinner