#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "../logger/eventLog.hpp"
#include "fork.hpp"
#include "../waiter/waiter_without_queue.hpp"

namespace dinner{

std::atomic_bool ready = {false};

class fork;

struct philosopher_setting
{
    philosopher_setting(int _number_at_the_table,
        waiter_without_queue & _waiter,
        std::chrono::milliseconds _thinking_time,
        std::chrono::milliseconds _eating_time,
        std::chrono::milliseconds _falling_time,
        int _count_eat)

    : m_log{ std::to_string( _number_at_the_table) }
    , m_count_eat(_count_eat)
    , m_eating_time{_eating_time}
    , m_thinking_time{_thinking_time}
    , m_falling_time{_falling_time}
    , m_waiter{_waiter}
    , m_number_at_the_table{_number_at_the_table}
    {};

    int m_count_eat;
    int m_number_at_the_table;
    std::chrono::milliseconds m_thinking_time;
    std::chrono::milliseconds m_eating_time;
    std::chrono::milliseconds m_falling_time;
    waiter_without_queue& m_waiter;
    dinner::lib_logger::PhilosopherEventLog m_log;
};


class philosopher
{
    
public:

    philosopher( philosopher_setting _philosopher_setting)
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

    void work()
    {
        while (!ready);

        for(int i = 0; i < m_philosopher_setting.m_count_eat; ++i)
        {
            think();
            eat();

        }
        
        m_philosopher_setting.m_log.startActivity(dinner::lib_logger::ActivityType::leave);
    };

    const lib_logger::PhilosopherEventLog& eventLog() const 
    { 
        return m_philosopher_setting.m_log; 
    };


private:

    void eat()
    {
        bool begin_left{false};
        while(!m_philosopher_setting.m_waiter.forks_take(m_philosopher_setting.m_number_at_the_table) ){
            if (!begin_left)
            {
                m_philosopher_setting.m_log.startActivity(dinner::lib_logger::ActivityType::eatFailure); 
                begin_left = true;
            }
        }
        if(begin_left){
            m_philosopher_setting.m_log.endActivity(lib_logger::ActivityType::eatFailure);
        }

        wait( lib_logger::ActivityType::eat, m_philosopher_setting.m_eating_time );
        
        m_philosopher_setting.m_waiter.forks_put(m_philosopher_setting.m_number_at_the_table);

    };

    inline void wait( lib_logger::ActivityType activity_type, std::chrono::milliseconds numMs) 
    { 
        m_philosopher_setting.m_log.startActivity(activity_type);
        std::this_thread::sleep_for(std::chrono::milliseconds(numMs)); 
        m_philosopher_setting.m_log.endActivity( activity_type );

    };


    void think()
    {
        wait(lib_logger::ActivityType::think , m_philosopher_setting.m_thinking_time );
    };

    philosopher_setting m_philosopher_setting;

    std::thread m_lifethread;

    // int m_number_at_the_table;
};
}; //namespace dinner