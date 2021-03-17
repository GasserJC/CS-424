#include "ProdCons.hpp"

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
NOTE: BASH COMMAND TO RUN IS:       !
                                    !
$ g++ main.cpp -pthread             !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

This File Contains Main Thread Logic and the Abstraction of the issue.
    ProdCons.hpp => producer and consumer logic
    Semaphore.hpp => Semaphore Mutex Class to prevent race conditions
    Rando.hpp => A thread safe Random Number Generator

!!!
    You may find K, N, T in ProdCons.hpp
!!!

Race Condition Triggers:
    Any values of k, N, T could cause a race condition.
    If either process happens to be processing faster than another, (even if k = 1).
    Then eventually that faster process will lap the other (ie: race condition)

    Personally I used:
    T = 3
    K = 6
    N = 12
    and still got race conditions.

*/

void run(int buffer[], int n, int k, int t) {
    try{
        std::thread prod(Producer, std::ref(buffer), n, k, t);
        std::thread cons(Consumer, std::ref(buffer), n, k, t);
        cons.join();
        prod.join();
    } catch(...) {
        std::cout << std::endl << "!! Terminated the Threads !!" << std::endl;
    }
}

void mainThread(int buffer[], int n, int k, int t) {
    std::thread MainT(run, std::ref(buffer), n, k, t);
    MainT.join();
}

int main() {

    int buffer[N];
    //initialize the buffer
    for (int i = 0; i < N; i++) {
        buffer[i] = 0;
    }
    //Call Main Thread
    std::cout << std::endl << "There is no auto-terminate!" << std:: endl;
    std::cout << std::endl << "Starting Main Thread" << std:: endl;
    mainThread(buffer, N, K, T);
    std::cout << std::endl << "Finished Main Thread." << std::endl;

    return 1;
}

