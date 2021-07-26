#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "eventLog.hpp"
#include "fork.hpp"
// #include "waiter.hpp"
#include "waiter.hpp"

std::atomic_bool ready = {false};

class fork;

class philosopher
{
    
public:
    philosopher(int _number_at_the_table, const char * _m_name, waiter& _waiter, int _m_thinking_time, int _m_eating_time, int _m_count_eat)
    : m_count_eat{_m_count_eat}
    , m_log{ m_name}
    , m_name{_m_name}
    , m_number_at_the_table{_number_at_the_table}
    , m_thinking_time{_m_thinking_time}
    , m_eating_time{_m_eating_time}
    , m_lifethread{&philosopher::work, this}
    , m_done{false}
    , m_waiter{_waiter}
    {};

    ~philosopher()
    {
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
        
        m_log.startActivity(ActivityType::leave);
        m_done = true;
    };


    void eat()
    {
        bool begin_left{false};
        while(!m_waiter.forks_take(m_number_at_the_table) ){
            if (!begin_left)
            {
                m_log.startActivity(ActivityType::eatFailure); 
                begin_left = true;
            }
        }
        if(begin_left){
            m_log.endActivity(ActivityType::eatFailure);
        }


        m_log.startActivity( ActivityType::eat );
        wait( m_eating_time );
        m_log.endActivity( ActivityType::eat );
        
        m_waiter.forks_put(m_number_at_the_table);

    };

    void think()
    {
        m_log.startActivity(ActivityType::think);
        wait( m_thinking_time );
        m_log.endActivity( ActivityType::think );
    };


    const PhilosopherEventLog& eventLog() const 
    { 
        return m_log; 
    };

    bool isDone(){
        return m_done;
    };

private:

    int m_number_at_the_table;     
    const char * m_name;
    int m_thinking_time;
    int m_eating_time;
    int m_count_eat;
    waiter &m_waiter;
    PhilosopherEventLog m_log;
    std::thread m_lifethread;
    bool m_done;
};
