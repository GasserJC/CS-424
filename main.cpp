#include "producer.hpp"
#include "consumer.hpp"
#include <iostream>
#include <thread>  

    
const int N = 100;
const int K = 20;
const int T = 4;

void mainThread(int buffer[], int k, int t){
    //Producer prod;
   //Consumer cons;
    std::cout << "hello world";
    //prod.produce(buffer, k, t);
    //cons.consume(buffer, k, t);
}

int main(){
    int buffer [N];

    //initialize the buffer
    for(int i = 0; i < N; i++){
        buffer[i] = 0;
    }

    //Call Main Thread
    std::thread Host (mainThread, std::ref(buffer), K, T);
    std::cout << "Started Main Thread." << std::endl;
    Host.join();
    std::cout << "Finished Main Thread." << std::endl;
    return 1;
}

