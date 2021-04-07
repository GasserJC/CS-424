#ifndef BANKER
#define BANKER

#include <iostream>
#include <thread>

void Request(int I,int J,int K){
    std::cout << I, K, K;
}

void Release(int I,int J,int K){
    
}


void Manual(int Max [], int Allocation [], int Available [], int Resources, int Processes){
    std::string cmd;
    int I,J,K;
    while(true){
        std::cout << "Enter Request:";
        std::cin >> cmd;

        if(cmd[0] == 'r'){
            try{
                if(cmd[2] == 'q'){ //request cmd
                    Request(I,J,K);
                } else { //release cmd
                    Release(I,J,K);
                }   
            } catch (...){ //impropper user input
                std::cout << "impropper user input \n options are: \n request I of J for K \n release I of J for K \n end \n";
            }
        } else if(cmd == "end"){
            std::cout << "Ending Manual Mode.";
            break;
        } else {
            std::cout << "impropper user input \n options are: \n request I of J for K \n release I of J for K \n end \n";
        }
    }
}

void Auto(int Max [], int Allocation [], int Available [], int Resources, int Processes){
    std::vector<std::thread> Pool;
    for(int i = 0; i < Processes; i++){
        //std::thread prod(func, param1, ..., param2);
        Pool.push_back(std::thread(Request, 0*i, 1*i, 2*i));
    }

    for(int i = 0; i < Processes; i++){
        Pool[i].join();
    }
    //Automatic
        //create 1 thread for each n process 
        //each thread generates 3 random requests and 3 release commands for itself
        //requests alternate with releases
        //after the requests and releases are done, terminate the thread
        //terminate the program after all threads are done
    std::cout << "Auto Thread Finish";
}

#endif