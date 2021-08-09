#pragma once

namespace dinner{

class waiter
{
public:
    waiter(std::vector<fork> & _forks)
    :m_forks{_forks}
    {};

    virtual ~waiter(){};
    
    bool forks_take(int index_philosopher) 
    {
        if( can_take_fork(index_philosopher) )
        {
            return true;  
        };
        return false;
    };
    
    void forks_put(int index_philosopher) 
    {
        if( index_philosopher+1 != m_forks.size())
        {
            m_forks.at(index_philosopher).put_fork();
            m_forks.at(index_philosopher+1).put_fork();
            return;
        }
        m_forks.at(index_philosopher).put_fork();
        m_forks.at(0).put_fork();
    };
private:
    virtual bool can_take_fork(int index_philosopher)
    {
        return false;
    };

    std::vector<fork> &m_forks;

};
} // namespace dinner