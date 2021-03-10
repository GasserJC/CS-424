#include "producer.hpp"
#include "consumer.hpp"
#include <iostream>
#include <thread>  

    
const int n = 100;
const int k = 20;
const int t = 4;

void mainThread(int* buffer, int kk, int tt){
    // start producer
    // start consumer

    std::thread prod(&Producer::produce, &buffer, kk, tt);
    std::thread cons(&Consumer::consume, &buffer, kk, tt);

    prod.join();
    cons.join();
}

int main(){
    int buffer [n];

    //initialize the buffer
    for(int i = 0; i < n; i++){
        buffer[i] = 0;
    }

    //Call Main Thread
    std::thread Host (mainThread, &buffer, k, t);
    std::cout << "Started Main Thread." << std::endl;
    Host.join();
    std::cout << "Finished Main Thread." << std::endl;
    return 1;
}

