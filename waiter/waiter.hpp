#pragma once

namespace waiter_solution{

class waiter
{
public:
    virtual ~waiter(){};
    virtual bool forks_take(int index_philosopher) { return false;};
    virtual void forks_put(int index_philosopher) = 0;

};
}; // namespace waiter_solution