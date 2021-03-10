#include "producer.hpp"
#include "consumer.hpp"
#include <iostream>
#include <thread>  

    
const int N = 100;
const int K = 20;
const int T = 4;

void foo(int* buffer, int k, int t){

}

void mainThread(int buffer[], int k, int t){
    std::thread prod(foo, std::ref(buffer), k, t);
    std::thread cons(foo, std::ref(buffer), k, t);

    prod.join();
    cons.join();
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

