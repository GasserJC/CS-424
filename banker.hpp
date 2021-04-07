#ifndef BANKER
#define BANKER

#include <iostream>
#include <thread>
#include "Rando.hpp"
#include "detect.hpp"

void Request(int I,int J,int K){
    std::cout << "\nRequest " << I << " of " << J << " for " << K;

    //process K makes a request for I many resources of resource J
    if(I <= NEED[K*PROCESSES + J] || I <= AVAILABLE[K*PROCESSES + J]){

        //Grant Request
        ALLOCATION[K*PROCESSES + J] += I;
        AVAILABLE[J] -= I;

        if(!HasSafeState()){
            //Undo Request
            ALLOCATION[K*PROCESSES + J] -= I;
            AVAILABLE[J] += I;
            std::cout << "\nRequest " << I << " of " << J << " for " << K << " !!! FAILED !!!";
        } else {
            std::cout << "\nRequest " << I << " of " << J << " for " << K << " !!! PASSED !!!";
        }
    }
}

void Release(int I,int J,int K){
    //process K releases for I many resources of resource J
}

void Bankers(){
    Seed(PROCESSES*RESOURCES);
    int Unit[6];
    int Resource[6];
    int Process[6];

    //Make three requests and releases
    // arr = {request, release, ...}
    for(int i = 0; i < 6; i++){
        Process[i] = int(RANDOM() * PROCESSES);
        Resource[i] = int(RANDOM() * RESOURCES);
        Unit[i] = int(RANDOM() * MAX[Process[i]*PROCESSES + Resource[i]]);
    }

    //Alternate Requests and Releases
    for(int i = 0; i < 6; i++){
        if( i % 2 == 0){
           Request(Unit[i], Resource[i], Process[i]);
        } else {
           Release(Unit[i], Resource[i], Process[i]);
        }
    }
}

void ManualThread(){
    std::string cmd;
    int I,J,K;
    while(true){
        std::cout << std::endl; << "Enter Request:";
        std::getline(std::cin, cmd);

        if(cmd[0] == 'r'){
            try{
                if(cmd[2] == 'q'){ //request cmd
                    I = int(cmd[8])  - 48;
                    J = int(cmd[13])  - 48;
                    K = int(cmd[19])  - 48;
                    Request(I,J,K);
                } else { //release cmd
                    I = int(cmd[8])  - 48;
                    J = int(cmd[13])  - 48;
                    K = int(cmd[19])  - 48;
                    Release(I,J,K);
                }   
            } catch (...){ //impropper user input
                std::cout << "\nimpropper user input \n options are: \n request I of J for K \n release I of J for K \n end \n";
            }
        } else if(cmd == "end"){ //user wants to end
            std::cout << "\nEnding Manual Mode.";
            break;
        } else {
            std::cout << "\nimpropper user input \n options are: \n request I of J for K \n release I of J for K \n end \n";
        }
    }
}

void Manual(){
    std::thread ManualSimulation(ManualThread);
    ManualSimulation.join();
}


void Auto(){

    //Automatic
    //create 1 thread for each n process 
        //each thread generates 3 random requests and 3 release commands for itself
            //requests alternate with releases
            //after the requests and releases are done, terminate the thread
    //terminate the program after all threads are done

    std::vector<std::thread> Pool;
    for(int i = 0; i < PROCESSES; i++){
        Pool.push_back(std::thread(Bankers));
    }

    for(int i = 0; i < PROCESSES; i++){
        Pool[i].join();
    }
    std::cout << "Auto Thread Finish";
}

#endif