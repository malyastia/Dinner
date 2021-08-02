#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "../logger/eventLog.hpp"
#include "fork.hpp"
#include "../waiter/waiter.hpp"

namespace philosopher{

std::atomic_bool ready = {false};

class fork;

struct philosopher_setting
{
    philosopher_setting(std::string _name, waiter_solution::waiter& _waiter, std::chrono::milliseconds _thinking_time, std::chrono::milliseconds _eating_time, int _count_eat)
    : m_log{ _name}
    , m_name{_name}
    , m_thinking_time{_thinking_time}
    , m_eating_time{_eating_time}
    , m_waiter{_waiter}
    , m_count_eat(_count_eat)
    {};

    int m_count_eat;
    std::string m_name;
    std::chrono::milliseconds m_thinking_time;
    std::chrono::milliseconds m_eating_time;
    waiter_solution::waiter& m_waiter;
    logger::PhilosopherEventLog m_log;
};


class philosopher
{
    
public:

    philosopher(int _number_at_the_table, philosopher_setting _philosopher_setting)
    : m_count_eat{_philosopher_setting.m_count_eat}
    , m_log{  std::to_string( _number_at_the_table ) }
    , m_name { _philosopher_setting.m_name }
    , m_number_at_the_table { _number_at_the_table}
    , m_thinking_time{_philosopher_setting.m_thinking_time}
    , m_eating_time{_philosopher_setting.m_eating_time}
    // , m_waiter{_philosopher_setting.m_waiter}
    , m_lifethread { &philosopher::work, this }
    , m_philosopher_setting {_philosopher_setting}
    {
        // m_lifethread.join();
    };

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
        m_lifethread.join();
    }; 

    void work()
    {
        while (!ready);

        for(int i = 0; i < m_count_eat; ++i)
        {
            think();
            eat();

        }
        
        m_log.startActivity(logger::ActivityType::leave);
    };

    const logger::PhilosopherEventLog& eventLog() const 
    { 
        return m_log; 
    };


private:

    void eat()
    {
        bool begin_left{false};
        while(!m_philosopher_setting.m_waiter.forks_take(m_number_at_the_table) ){
            if (!begin_left)
            {
                m_log.startActivity(logger::ActivityType::eatFailure); 
                begin_left = true;
            }
        }
        if(begin_left){
            m_log.endActivity(logger::ActivityType::eatFailure);
        }


        m_log.startActivity( logger::ActivityType::eat );
        wait( m_eating_time );
        m_log.endActivity( logger::ActivityType::eat );
        
        m_philosopher_setting.m_waiter.forks_put(m_number_at_the_table);

    };

    inline void wait(std::chrono::milliseconds numMs) 
    { 
        std::this_thread::sleep_for(std::chrono::milliseconds(numMs)); 
    };


    void think()
    {
        m_log.startActivity(logger::ActivityType::think);
        wait( m_thinking_time );
        m_log.endActivity( logger::ActivityType::think );
    };



    int m_number_at_the_table;     
    std::string m_name;
    std::chrono::milliseconds m_thinking_time;
    std::chrono::milliseconds m_eating_time;
    int m_count_eat;
    // waiter_solution::waiter &m_waiter;
    logger::PhilosopherEventLog m_log;

    philosopher_setting& m_philosopher_setting;

    std::thread m_lifethread;
};
}; //namespace philosopher