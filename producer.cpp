#include "producer.hpp"
#include <stdlib.h>   
#include <time.h>  
#include <chrono> 
#include <thread> 
#include <iostream>

void Producer::produce(int * buffer, int k, int t){
    int MaxWrite = (rand() % k) % (sizeof(&buffer)/sizeof(buffer)); //confirms k is never bigger than buffer
    int MaxTime = (rand() % t);
    int i = 0;

    while(MaxWrite <= 0){ //continues while able to write

        if(k == 0){
            MaxWrite = (rand() % k) % (sizeof(&buffer)/sizeof(buffer));
            std::this_thread::sleep_for(std::chrono::seconds(MaxTime));
            MaxTime = (rand() % t);
        }

        buffer[i]++;   
        MaxWrite--;
        i = (i+1) % (sizeof(&buffer)/sizeof(buffer));
    }

    std::cout << "Race Condition Failure (Producer Wrote a 2)" << std::endl;
}
