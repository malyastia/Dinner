#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <string>
#include "eventLog.cpp"

namespace Dinning_philosophers
{
    constexpr int max_food = 1000;

    template<std::size_t count> 
    class fork
    {
    public:
        std::array<std::mutex, count> forks;
        std::atomic<bool> start{false};
    };

    class philosopher
    {
        
    public:
        philosopher(std::string _name, std::mutex &l, std::mutex &r, int _thinking_time, int _eating_time)
        : name(_name)
        , left_fork(l)
        , right_fork(r)
        , thinking_time(_thinking_time)
        , eating_time(_eating_time)
        , lifethread(&philosopher::work, this)
        {};

        ~philosopher()
        {
            lifethread.join();
        };

        void work()
        {
            
            while( !full )
            {
                think();
                eat();
            };

        };

        void think()
        {
            //log.print(activityType::think);
            std::this_thread::sleep_for(std::chrono::milliseconds( thinking_time ) );

        }

        void eat()
        {
            //log.print(activityType::eat);
            if (!full){
                std::lock(left_fork, right_fork);

                std::lock_guard<std::mutex> left_lock(left_fork, std::adopt_lock);
                std::lock_guard<std::mutex> right_lock(right_fork, std::adopt_lock);
                printf("%s is eating\n",name.c_str());

                std::this_thread::sleep_for(std::chrono::milliseconds( eating_time ));
                food_eaten.fetch_add(eating_time);
                printf("%s food_eaten %d\n",name.c_str(), food_eaten.load());
                
                if( food_eaten >= max_food )
                {
                    full = true;
                }
                return;
            }

        };

        void print(){
            
        };
    private:

        std::string name;
        std::mutex &left_fork;
        std::mutex &right_fork;
        std::thread lifethread;
        std::atomic<int> food_eaten{0};
        std::atomic_bool full{false};
        int thinking_time;
        int eating_time;

    };

    void dinner()
    {
        std::cout << "Dinner started!" << std::endl;
        {
            const size_t eat_count = 5;
            fork<eat_count> fork;
            std::array<philosopher, eat_count> philosophers
            {
                {
                    {"0", fork.forks[0], fork.forks[1], 50, 1000},
                    {"1", fork.forks[1], fork.forks[2], 50, 1000},
                    {"2", fork.forks[2], fork.forks[3], 50, 1000},
                    {"3", fork.forks[3], fork.forks[4], 50, 60},
                    {"4", fork.forks[4], fork.forks[0], 50, 1000}
                }
            };
        }
        std::cout << "Dinner done!" << std::endl;

    }
};

int main()
{
    Dinning_philosophers::dinner();
    return 0;
}