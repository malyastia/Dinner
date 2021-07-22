#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "eventLog.hpp"
#include "fork.hpp"
#include "waiter.hpp"

std::atomic_bool ready = {false};

class fork;

class philosopher
{
    
public:
    philosopher(const char * _m_name,  int _m_thinking_time, int _m_eating_time, int _m_count_eat, fork &_m_right_fork, fork &_m_left_fork)
    : m_count_eat(_m_count_eat)
    , log( m_name)
    , m_name(_m_name)
    , m_thinking_time(_m_thinking_time)
    , m_eating_time(_m_eating_time)
    , m_lifethread(&philosopher::work, this)
    , m_done(false)
    , m_right_fork(_m_right_fork)
    , m_left_fork(_m_left_fork)
    // , m_waiter(_waiter)
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
        log.startActivity(ActivityType::leave);
        m_done = true;
    };


    void eat()
    {
        bool begin_left{false};
        while(!m_left_fork.take_fork()){
            if (!begin_left)
            {
                log.startActivity(ActivityType::eatFailure); 
                begin_left = true;
            }
        }
        log.endActivity(ActivityType::eatFailure);
        

        bool begin_right{ false};

        while(!m_right_fork.take_fork() )
        {
            if (!begin_right)
            {
                log.startActivity(ActivityType::eatFailure);
                begin_right = true;
            }
        }
        log.endActivity(ActivityType::eatFailure);
        

        log.startActivity( ActivityType::eat );
        wait( m_eating_time );
        log.endActivity( ActivityType::eat );
        
        m_right_fork.put_fork();
        m_left_fork.put_fork();

    };

    void think()
    {
        log.startActivity(ActivityType::think);
        wait( m_thinking_time );
        log.endActivity( ActivityType::think );
    };


    const PhilosopherEventLog& eventLog() const 
    { 
        return log; 
    };

    bool isDone(){
        return m_done;
    };

private:
    
    const char * m_name;
    int m_thinking_time;
    int m_eating_time;
    int m_count_eat;
    // waiter &m_waiter;
    fork &m_right_fork;
    fork &m_left_fork;
    PhilosopherEventLog log;
    std::thread m_lifethread;
    bool m_done;
};
