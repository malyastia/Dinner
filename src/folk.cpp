
#include <iostream>
#include <atomic>
#include <mutex>

namespace Dinning_philosophers{
template<std::size_t count> 
    class fork
    {
    public:
        std::array<std::mutex, count> forks;
        std::atomic_bool start{false};
    };
}