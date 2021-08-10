#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>


#include "fork.hpp"
#include "../waiter/unique_take.hpp"

namespace dinner{

std::atomic_bool ready = {false};

template<class _waiter_T>
struct philosopher_setting
{
    philosopher_setting(int _number_at_the_table,
        _waiter_T & _waiter,
        std::chrono::milliseconds _thinking_time,
        std::chrono::milliseconds _eating_time,
        std::chrono::milliseconds _falling_time,
        int _count_eat)

    : m_log{ std::to_string( _number_at_the_table) }
    , m_count_eat(_count_eat)
    , m_eating_time{_eating_time}
    , m_thinking_time{_thinking_time}
    , m_falling_time(_falling_time)
    , m_waiter(_waiter)
    , m_number_at_the_table{_number_at_the_table}
    {};

    int m_count_eat;
    int m_number_at_the_table;
    std::chrono::milliseconds m_thinking_time;
    std::chrono::milliseconds m_eating_time;
    std::chrono::milliseconds m_falling_time;
    _waiter_T& m_waiter;
    PhilosopherEventLog m_log;
};

template<class _waiter_T>
class philosopher
{
    
public:
    
    philosopher( philosopher_setting<_waiter_T> _philosopher_setting)
    : m_lifethread { &philosopher::work, this }
    , m_philosopher_setting {_philosopher_setting}
    {};

    ~philosopher()
    {
        if ( m_lifethread.joinable() )
        {
            m_lifethread.join();
        }
    };
    
    void joining_thread()
    {
        if ( m_lifethread.joinable() )
        {
            m_lifethread.join();
        }
    }; 

    const PhilosopherEventLog& eventLog() const 
    { 
        return m_philosopher_setting.m_log; 
    };

private:

    void work()
    {
        while (!ready);

        bool f = true;

        for(int i = 0; i < m_philosopher_setting.m_count_eat;)
        {
            think();
            

            if(  eat() )
            {
                ++i;
            }
            else
            {
                waiting_falling_time();
            }
        }
        
        m_philosopher_setting.m_log.startActivity( ActivityType::leave);
    };

    bool eat()
    {
        unique_take forks_taken = m_philosopher_setting.m_waiter.forks_take(m_philosopher_setting.m_number_at_the_table);

        if( !forks_taken ){
            return false;
        }

        m_philosopher_setting.m_log.startActivity(ActivityType::eat);
        wait(m_philosopher_setting.m_eating_time ); 
        m_philosopher_setting.m_log.endActivity( ActivityType::eat );
        
        return true;
        
        

    };

    inline void wait( std::chrono::milliseconds numMs) 
    { 
        std::this_thread::sleep_for(std::chrono::milliseconds(numMs));
    };

    void waiting_falling_time()
    {
        m_philosopher_setting.m_log.startActivity( ActivityType::eatFailure);
        wait( m_philosopher_setting.m_falling_time );
        m_philosopher_setting.m_log.endActivity( ActivityType::eatFailure);
    };


    void think()
    {
        m_philosopher_setting.m_log.startActivity( ActivityType::think);
        wait( m_philosopher_setting.m_thinking_time );
        m_philosopher_setting.m_log.endActivity( ActivityType::think);

    };


    philosopher_setting<_waiter_T> m_philosopher_setting;

    std::thread m_lifethread;

};
} //namespace dinner