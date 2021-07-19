#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "eventLog.hpp"
#include "fork.hpp"


std::atomic_bool ready = {false};

class philosopher
{
    
public:
    philosopher(const char * _name, int _thinking_time, int _eating_time, int _count_eat)
    : count_eat(_count_eat)
    , log( name)
    , name(_name)
    , thinking_time(_thinking_time)
    , eating_time(_eating_time)
    {};

    ~philosopher()
    {};
    
    void work()
    {
        while (!ready);

        for(int i = 0; i < count_eat; ++i)
        {
            think();
            eat();

        }
    };


    void eat()
    {
        log.startActivity( ActivityType::eat );
        wait( eating_time );
        log.endActivity( ActivityType::eat );

    };

    void think()
    {
        log.startActivity(ActivityType::think);
        wait( thinking_time );
        log.endActivity( ActivityType::think );
    };


    const PhilosopherEventLog& eventLog() const 
    { 
        return log; 
    };

private:
    const char * name;
    int thinking_time;
    int eating_time;
    int count_eat;
    PhilosopherEventLog log;
};
