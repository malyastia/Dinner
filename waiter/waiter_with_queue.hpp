#pragma once
#include "fork.hpp"

namespace dinner{

class unique_take
{
public:
    unique_take()
    : m_left_fork(nullptr)
    , m_right_fork(nullptr)
    , m_success_take (false)
    {};

    unique_take(fork* _left_fork, fork* _right_fork)
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

    unique_take( unique_take&& unique_take_class)
    : m_left_fork(unique_take_class.m_left_fork)
    , m_right_fork(unique_take_class.m_right_fork)
    , m_success_take ( unique_take_class.m_success_take)
    {
        unique_take_class.m_left_fork = nullptr;
        unique_take_class.m_right_fork = nullptr;
        unique_take_class.m_success_take=false;

    };

    unique_take( const unique_take&) = delete;

    unique_take& operator=( const unique_take& ) = delete;

    unique_take& operator=( unique_take&& unique_take_class)
    {
        if(&unique_take_class == this)
        {
            return *this;
        }
        
        m_left_fork = unique_take_class.m_left_fork;
        m_right_fork = unique_take_class.m_right_fork;
        m_success_take = unique_take_class.m_success_take;

        unique_take_class.m_left_fork = nullptr;
        unique_take_class.m_right_fork = nullptr;
        unique_take_class.m_success_take=false;

        return *this;
    };

    operator bool() const 
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