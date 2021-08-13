#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>


#include "fork.hpp"
#include "../waiter/unique_take.hpp"
#include "../waiter/waiter_with_queue.hpp"

namespace dinner{

class start_eating_philosopher{

public:

    void start()
    {
        ready = true;
    };

    bool is_start(){
        return ready;
    }

private:
    std::atomic_bool ready = {false};

};


template<class _waiter_T>
struct philosopher_setting
{
    philosopher_setting(int number_at_the_table,
        start_eating_philosopher& start_eating,
        _waiter_T & waiter,
        std::chrono::milliseconds thinking_time,
        std::chrono::milliseconds eating_time,
        std::chrono::milliseconds falling_time,
        int count_eat)
    : m_log{ std::to_string( number_at_the_table) }
    , m_count_eat( count_eat)
    , m_eating_time{ eating_time}
    , m_thinking_time{ thinking_time}
    , m_falling_time( falling_time)
    , m_waiter( waiter)
    , m_start_eating_philosopher (start_eating)
    , m_number_at_the_table{ number_at_the_table}
    {};

    int m_count_eat;
    int m_number_at_the_table;
    std::chrono::milliseconds m_thinking_time;
    std::chrono::milliseconds m_eating_time;
    std::chrono::milliseconds m_falling_time;
    _waiter_T& m_waiter;
    start_eating_philosopher& m_start_eating_philosopher;
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
        while (! m_philosopher_setting.m_start_eating_philosopher.is_start());

        bool f = true;
        int i = m_philosopher_setting.m_count_eat;
        while ( i > 0 )
        {
            think();            

            if(  !eat(i) )
            {
                waiting_falling_time();
            }
        }
        
        m_philosopher_setting.m_log.startActivity( ActivityType::leave);
    };

    bool eat(int& count_food_eaten)
    {
        unique_take forks_taken{m_philosopher_setting.m_waiter.forks_take(m_philosopher_setting.m_number_at_the_table)};
            
        if( !forks_taken ){
            return false;
        }
        --count_food_eaten;

        logging(ActivityType::eat);
        
        return true;
    };

    inline void wait( std::chrono::milliseconds numMs) 
    { 
        std::this_thread::sleep_for(std::chrono::milliseconds(numMs));
    };

    void waiting_falling_time()
    {
       logging(ActivityType::eatFailure);
    };


    void think()
    {
       logging(ActivityType::think);
    };

    void logging(ActivityType type)
    {
         m_philosopher_setting.m_log.startActivity( type);
        wait( m_philosopher_setting.m_thinking_time );
        m_philosopher_setting.m_log.endActivity( type);
    };


    philosopher_setting<_waiter_T> m_philosopher_setting;

    std::thread m_lifethread;

};
} //namespace dinner