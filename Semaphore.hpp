#ifndef SEMAPHORE
#define SEMAPHORE

#include <mutex> 
#include <condition_variable>

class Semaphore {
    std::mutex Mutx;
    std::condition_variable condition;
    static const int CountMax = 1;
    int Count;
public:
    explicit Semaphore(int InitialCount = CountMax) : Count(InitialCount) {}

    void wait()
    {
        std::unique_lock<std::mutex> lock(Mutx);
        condition.wait(lock, [=] { 
            return (0 < Count); 
        });
        Count--;
    }

    void signal()
    {
        std::lock_guard<std::mutex> lock(Mutx);
        if (Count <= CountMax) {
            Count++;
            condition.notify_one();
        }
    }

    bool TryWait()
    {
        std::lock_guard<std::mutex> lock(Mutx);
        if (0 < Count) {
            Count--;
            return true;
        } else {
            return false;
        }
    }

    void lock() { wait(); }
    bool try_lock() { return TryWait(); }
    void unlock() { signal(); }
};

#endif