#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <string>
#include <random>

constexpr int max_food = 1000;
constexpr int count = 5;

class Fork{
public:
    std::array<std::mutex, count> forks;
    std::atomic<bool> start{false};
};

class Philosopher{
private:
    std::string name;
    std::mutex &left_fork;
    std::mutex &right_fork;
    std::thread lifethread;
    std::atomic<int> food_eaten{0};
    Fork const &forks;
    std::atomic<bool> full{false};
    std::mt19937 rng{std::random_device{}()};
    
public:
    Philosopher(std::string_view _name, Fork &f,std::mutex &l, std::mutex &r)
    : name(_name), forks(f) ,left_fork(l), right_fork(r), lifethread(&Philosopher::work, this)
    {};

    ~Philosopher()
    {
        lifethread.join();
    };

    void work()
    {
        while(!forks.start);

        while( !full )
        {
            think();
            eat();
        };

    };

    void think()
    {
        printf("%s is thinking \n",name.c_str());
        static thread_local std::uniform_int_distribution<> wait(1, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds( wait(rng) * 100 ) );

    }

    void eat()
    {
        if (!full){
            std::lock(left_fork, right_fork);

            std::lock_guard<std::mutex> left_lock(left_fork, std::adopt_lock);
            std::lock_guard<std::mutex> right_lock(right_fork, std::adopt_lock);
            printf("%s is eating\n",name.c_str());

            static thread_local std::uniform_int_distribution<> dist(1, 10);
            std::this_thread::sleep_for(std::chrono::milliseconds( dist(rng)*100 ));
            food_eaten.fetch_add( dist(rng)*50 );
            printf("%s food_eaten %d\n",name.c_str(), food_eaten.load(std::memory_order_release ));
            
            if( food_eaten >= max_food )
            {
                full = true;
            }
            return;
        }

    }

};

void dinner()
{
    Fork fork;
    std::array<Philosopher, count> philosophers
    {
        {
            {"0", fork, fork.forks[0], fork.forks[1]},
            {"1", fork, fork.forks[1], fork.forks[2]},
            {"2", fork, fork.forks[2], fork.forks[3]},
            {"3", fork, fork.forks[3], fork.forks[4]},
            {"4", fork, fork.forks[4], fork.forks[0]}
        }
    };

    fork.start = true;

}


int main()
{
    dinner();
    return 0;
}