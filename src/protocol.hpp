#pragma once

class protocol
{
public:
    virtual ~protocol(){};
    virtual bool forks_take(int index_philosopher) { return false;};
    virtual void forks_put(int index_philosopher) = 0;

};