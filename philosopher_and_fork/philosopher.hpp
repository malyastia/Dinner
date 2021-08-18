#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "fork.hpp"
#include "unique_take.hpp"
#include "waiter_with_queue.hpp"

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





class philosopher
{
    
public:


struct philosopher_setting
{
    philosopher_setting(int number_at_the_table,
        start_eating_philosopher& start_eating,
        waiter & waiter,
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
    waiter& m_waiter;
    start_eating_philosopher& m_start_eating_philosopher;
    PhilosopherEventLog m_log;
};
    
    philosopher( philosopher_setting _philosopher_setting)
    : m_lifethread { &philosopher::work, this }
    , m_philosopher_setting {_philosopher_setting}
    {};
    // philosopher()
    // : m_lifethread { &philosopher::work, this }
    // , m_philosopher_setting {_philosopher_setting}
    // {};

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
            if(f)
            {
                think();            
            }
            else{
                waiting_falling_time();
            }

            eat(i,f);
        }
        
        m_philosopher_setting.m_log.startActivity( ActivityType::leave);
    };
    
private:
    bool eat(int& count_food_eaten, bool& flag)
    {
        unique_take forks_taken{m_philosopher_setting.m_waiter.forks_take(m_philosopher_setting.m_number_at_the_table)};
            
        if( !forks_taken ){
            flag = false;
            return false;
        }
        --count_food_eaten;

        logging(m_philosopher_setting.m_eating_time, ActivityType::eat);
        flag = true;
        return true;
    };

private:
    inline void wait( std::chrono::milliseconds numMs) 
    { 
        std::this_thread::sleep_for(std::chrono::milliseconds(numMs));
    };

    void waiting_falling_time()
    {
       logging(m_philosopher_setting.m_falling_time, ActivityType::eatFailure);
    };

    void think()
    {
       logging(m_philosopher_setting.m_thinking_time, ActivityType::think);
    };

    void logging(std::chrono::milliseconds time,ActivityType type)
    {
        m_philosopher_setting.m_log.startActivity( type);
        wait( time );
        m_philosopher_setting.m_log.endActivity( type);
    };

private:
    philosopher_setting m_philosopher_setting;
    std::thread m_lifethread;

};
} //namespace dinner