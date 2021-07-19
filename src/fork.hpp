#pragma once
#include <iostream>
#include <atomic>
#include <mutex>

#include "philosopher.hpp"


class fork
{
public:
    bool is_free()
    {
         return m.try_lock();
    };

    bool take_fork()
    {
        if(is_free())
        {
            m.lock();
            return true;
        }
        return false;
    };
    
    void put_fork()
    {
        m.unlock();
    };
private:

    std::mutex m;
};
