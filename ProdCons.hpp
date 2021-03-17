#ifndef PRODCONS
#define PRODCONS

#include <thread>  
#include "Semaphore.hpp"
#include "Rando.hpp"
#include <iostream>
#include <chrono> 
#include <stdio.h>      
#include <stdlib.h>  

static const int N = 10;
static const int K = 5;
static const int T = 5;

Semaphore f(0);
Semaphore e(K);
Semaphore mutexBase(1);

void Producer(int buffer[], int n, int k, int t) {
    Seed(intRand(1, 1000));
    int MaxWrite = int((RANDOM() * k));
    int MaxTime = int((RANDOM() * t));
    int next_in = 0;

    while (true) {
        for (int i = 0; i < MaxWrite; i++) {
            e.wait();
            mutexBase.wait();
            ++buffer[(next_in + i) % n];
            mutexBase.signal();
            f.signal();
            std::cout << "w";
        }
        std::this_thread::sleep_for(std::chrono::seconds(MaxTime));
        std::cout << std::endl << "[";
        for (int i = 0; i < n; i++) {
            std::cout << buffer[i] << " , ";
        }
        std::cout << "]" << std::endl;
        next_in = (next_in + MaxWrite) % n;

        std::cout << ".";
        MaxWrite = int((RANDOM() * k));
        MaxTime = int((RANDOM() * t));
    }
}

void Consumer(int buffer[], int n, int k, int t) {
    Seed(intRand(1, 1000));
    int MaxRead = int((RANDOM() * k));
    int MaxTime = int((RANDOM() * t));
    int next_out = 0;

    while ( true ) {
        for (int i = 0; i < MaxRead; i++) {
            f.wait();
            mutexBase.wait();
            --buffer[(next_out + i) % n];
            mutexBase.signal();
            e.signal();
            std::cout << "r";
        }
        std::cout << std::endl << "[";
        for (int i = 0; i < n; i++) {
            std::cout << buffer[i] << " , ";
        }
        std::cout << "]" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(MaxTime));
        std::cout << ".";
        next_out = (next_out + MaxRead) % n;
        MaxRead = int((RANDOM() * k));
        MaxTime = int((RANDOM() * t));
    }
}

#endif