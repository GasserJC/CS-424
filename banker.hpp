#ifndef BANKER
#define BANKER

void Manual(int Max [], int Allocation [], int Available [], int Resources, int Processes){
    //Manual
        //the user can request any I of J for K
        //the user can release anu I of J for K
        //the user can end the program
}

void Auto(int Max [], int Allocation [], int Available [], int Resources, int Processes){
    //Automatic
        //create 1 thread for each n process 
        //each thread generates 3 random requests and 3 release commands for itself
        //requests alternate with releases
        //after the requests and releases are done, terminate the thread
        //terminate the program after all threads are done
}

#endif