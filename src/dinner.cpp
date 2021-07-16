#include "eventLog.hpp"
#include "folk.cpp"

#include <atomic>
#include <condition_variable>
#include <thread>
#include <shared_mutex>

namespace Dinning_philosophers
{
    std::atomic_bool ready = {false};

    inline void wait(int numMs) { std::this_thread::sleep_for(std::chrono::milliseconds(numMs)); }

    class philosopher
    {
        
    public:
        philosopher(const char * _name, int _thinking_time, int _eating_time, int _count_eat, std::mutex &l, std::mutex &r)
        : count_eat(_count_eat)
        , log( name)
        , name(_name)
        , left_fork(l)
        , right_fork(r)
        , thinking_time(_thinking_time)
        , eating_time(_eating_time)
        {};

        ~philosopher()
        {};

        void work()
        {
            while (!ready);

            for(int i = 0; i < count_eat; ++i)
            {
                think();
                eat();

            }
        };

        const PhilosopherEventLog& eventLog() const { return log; }

    private:
        void eat()
        {
            std::lock(left_fork, right_fork);
            std::lock_guard<std::mutex> left_lock(left_fork, std::adopt_lock);
            std::lock_guard<std::mutex> right_lock(right_fork, std::adopt_lock);
            log.startActivity( ActivityType::eat );
            wait( eating_time );
            log.endActivity( ActivityType::eat );

        };

        void think()
        {
            log.startActivity(ActivityType::eat);
            wait( thinking_time );
            log.endActivity( ActivityType::think );
        };

        const char * name;
        int thinking_time;
        int eating_time;
        int count_eat;
        std::mutex &left_fork;
        std::mutex &right_fork;
        PhilosopherEventLog log;
        std::mutex m;
    };

    template<typename _iterator>
    void dinner(_iterator begin_iteraton_philosopher, _iterator end_iteraton_philosopher)
    {
        
        std::thread threads[4];
        int i = 0;
        
        _iterator it = begin_iteraton_philosopher;
        {
            
            for ( i =0 ; i < 4 ; ++i)
            {
                threads[i] = std::thread( &philosopher::work, begin_iteraton_philosopher);
            }  
            
            ready = true;
        }

        {
            for ( i =0 ; i < 4 ; ++i)
            {
                threads[i].join();
            }  
        }

        std::cout << "Dinner started!" << std::endl;
        
        
        
        {
            _iterator it = begin_iteraton_philosopher;
            for( ; it != end_iteraton_philosopher; ++it )
            {
                it->eventLog().printSummary();
            }
        }
        

        std::cout << "Dinner done!" << std::endl;

            
        
        
        
        // {
        //     ready = true;
        //     for( ; i != 4; ++i )
        //     {
        //         threads[i].join();
        //     }
        // }
        //     {
        //         _iterator it = begin_iteraton_philosopher;
        //         for( ; it != end_iteraton_philosopher; ++it )
        //         {
        //             it->eventLog().printSummary();
        //         }
        //     }

            

    }

};

int main()
{

    const size_t eat_count = 4;
    Dinning_philosophers::fork<eat_count> forks;
    const size_t count_food = 2;
    std::array<Dinning_philosophers::philosopher, eat_count> philosophers
    {
        {
            {"0", 10, 30, count_food, forks.forks[0], forks.forks[1]},
            {"1", 20, 10, count_food, forks.forks[1], forks.forks[2]},
            {"2", 10, 10, count_food, forks.forks[2], forks.forks[3]},
            {"3", 20, 30, count_food, forks.forks[3], forks.forks[0]}
        }
    };


    Dinning_philosophers::dinner(std::begin(philosophers), std::begin(philosophers)+4 );
    
    return 0;
}