#pragma once
#include <iostream>
#include <atomic>
#include <mutex>

namespace dinner{
    
class fork
{
public:
    fork()
    {}

    fork( const fork&) = delete;

    fork& operator=( const fork& ) = delete;

    bool take_fork()
    {
        return m_fork_mutex.try_lock();
    }
    
    void put_fork()
    {
        m_fork_mutex.unlock();
    }

private:
    std::mutex m_fork_mutex;
};
} //namespace dinner