#pragma once
#include <iostream>
#include <atomic>
#include <mutex>


class fork
{
public:
    bool lock()
    {
        return m.try_lock();
    };
    
    void put_fork()
    {
        m.unlock();
    };
private:
    std::mutex m;
};
