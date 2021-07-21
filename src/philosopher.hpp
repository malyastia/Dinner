#pragma once
#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

#include "eventLog.hpp"
#include "fork.hpp"


std::atomic_bool ready = {false};

class fork;

class philosopher
{
    
public:
    philosopher(const char * _name, int _thinking_time, int _eating_time, int _count_eat, fork &_right_fork, fork &_left_fork)
    : count_eat(_count_eat)
    , log( name)
    , name(_name)
    , thinking_time(_thinking_time)
    , eating_time(_eating_time)
    , lifethread(&philosopher::work, this)
    , done(false)
    , right_fork(_right_fork)
    , left_fork(_left_fork)
    {};

    ~philosopher()
    {
        lifethread.join();
    };
    
    void work()
    {
        while (!ready);

        for(int i = 0; i < count_eat; ++i)
        {
            think();
            eat();

        }
        log.startActivity(ActivityType::leave);
        done = true;
    };


    void eat()
    {
        bool begin_left{false};
        while(!left_fork.lock()){
            if (!begin_left)
            {
                log.startActivity(ActivityType::eatFailure); 
                begin_left = true;
            }
        }
        log.endActivity(ActivityType::eatFailure);
        

        bool begin_right{ false};

        while(!right_fork.lock() )
        {
            if (!begin_right)
            {
                log.startActivity(ActivityType::eatFailure);
                begin_right = true;
            }
        }
        log.endActivity(ActivityType::eatFailure);
        

        log.startActivity( ActivityType::eat );
        wait( eating_time );
        log.endActivity( ActivityType::eat );
        
        left_fork.put_fork();
        right_fork.put_fork();

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

    bool isDone(){
        return done;
    };

private:
    
    const char * name;
    int thinking_time;
    int eating_time;
    int count_eat;
    fork &right_fork;
    fork &left_fork;
    PhilosopherEventLog log;
    std::thread lifethread;
    bool done;
};
