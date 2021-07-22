#pragma once
#include <iostream>
#include <atomic>
#include <mutex>


class fork
{
public:
    bool take_fork()
    {
        m_islock = m_fork_mutex.try_lock();
        return m_islock;
    };
    
    void put_fork()
    {
        m_fork_mutex.unlock();
    };

    bool is_taken()
    {
        return m_islock;
    };
private:
    bool m_islock;
    std::mutex m_fork_mutex;
};
