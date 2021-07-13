#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <string>



    enum class activityType{
        eat,
        think,
    };

class eventLog
{
    eventLog( std::string _philosopher)
    : philosopher(_philosopher)
    {};

    void print( activityType at )
    {
        switch (at)
        {
        case activityType::eat:
            printf("E");
            break;
        
        default:
            printf("T");
            break;
        }
    };

private:
    std::string philosopher;
};