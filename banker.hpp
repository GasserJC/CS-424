#ifndef BANKER
#define BANKER

#include <iostream>
#include <thread>
#include "Rando.hpp"
#include "detect.hpp"
#include <mutex>

std::mutex REQ;
std::mutex REL;

void Request(int I,int J,int K, int ID){
    REQ.lock();
    REL.lock();
    std::cout << "\nRequest " << I << " of " << J << " for " << K << " FROM " << ID;   
    //process K makes a request for I many resources of resource J
    if(I <= NEED[K*PROCESSES + J] || I <= AVAILABLE[K*PROCESSES + J]){

        //Grant Request   
        ALLOCATION[K*PROCESSES + J] += I;
        AVAILABLE[J] -= I;

        if(!HasSafeState()){
            //Undo Request
            ALLOCATION[K*PROCESSES + J] -= I;
            AVAILABLE[J] += I;
            std::cout << "\nRequest " << I << " of " << J << " for " << K << " !!! FAILED.0 !!!" << " from " << ID << " Failed the Safety Check." << "  Av2=" << AVAILABLE[2]; 
        } else {
            std::cout << "\nRequest " << I << " of " << J << " for " << K << " !!! PASSED !!!" << " from " << ID;
        }
    } else {
        std::cout << "\nRequest " << I << " of " << J << " for " << K << " !!! FAILED.1 !!!" << " from " << ID << " Failed to Request an acceptable amount.";
    }
    REQ.unlock();
    REL.unlock();
}

void Release(int I,int J,int K, int ID){
    //process K releases for I many resources of resource J
    REQ.lock();
    REL.lock();

    if((ALLOCATION[K*PROCESSES + J] - I) >= 0){
        ALLOCATION[K*PROCESSES + J] -= I;
        AVAILABLE[J] += I;
    }

    REQ.unlock();
    REL.unlock();
}

void Bankers(int ID){
    Seed(PROCESSES*RESOURCES*ID);
    int Unit[6];
    int Resource[6];
    int Process[6];

    //Make three requests and releases
    // arr = {request, release, ...}
    for(int i = 0; i < 6; i++){
        Process[i] = int(RANDOM() * PROCESSES)%PROCESSES;
        Resource[i] = int(RANDOM() * RESOURCES)%RESOURCES;
        Unit[i] = int(RANDOM() * MAX[Process[i]*RESOURCES + Resource[i]]) + 1;
    }

    //Alternate Requests and Releases
    for(int i = 0; i < 6; i++){
        if( i % 2 == 0){
           Request(Unit[i], Resource[i], Process[i], ID);
        } else {
           Release(Unit[i], Resource[i], Process[i], ID);
        }
    }
}

void ManualThread(){
    std::string cmd;
    int I,J,K;
    while(true){
        std::cout << std::endl << "Enter Request:";
        std::getline(std::cin, cmd);

        if(cmd[0] == 'r'){
            try{
                if(cmd[2] == 'q'){ //request cmd
                    I = int(cmd[8])  - 48;
                    J = int(cmd[13])  - 48;
                    K = int(cmd[19])  - 48;
                    Request(I,J,K,-1);
                } else { //release cmd
                    I = int(cmd[8])  - 48;
                    J = int(cmd[13])  - 48;
                    K = int(cmd[19])  - 48;
                    Release(I,J,K,-1);
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
        Pool.push_back(std::thread(Bankers, i));
    }

    for(int i = 0; i < PROCESSES; i++){
        Pool[i].join();
    }
    std::cout << "\nAuto Thread Finish";
}

#endif