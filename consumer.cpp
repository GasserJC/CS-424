#include "consumer.hpp"
#include <stdlib.h>   
#include <time.h>  
#include <chrono> 
#include <thread> 
#include <iostream>

void Consumer::consume(int* buffer, int k, int t) {
    int MaxRead = (rand() % k) % (sizeof(&buffer) / sizeof(buffer)); //confirms k is never bigger than buffer
    int MaxTime = (rand() % t);
    int i = 0;

    while (buffer[i] != 2 || MaxRead <= 0) { //continues until race condition

        if (k == 0) {
            MaxRead = (rand() % k) % (sizeof(&buffer) / sizeof(buffer));
            std::this_thread::sleep_for(std::chrono::seconds(MaxTime));
            MaxTime = (rand() % t);
        }

        while (buffer[i] == 0) { //stops while there is nothing new to read.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        buffer[i] = 0;
        MaxRead--;
        i = (i + 1) % (sizeof(&buffer) / sizeof(buffer));
    }

    std::cout << "Race Condition Failure (Consumer Read a 2)" << std::endl;
}