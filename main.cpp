#include <iostream>
#include <fstream>
#include "detect.cpp"

static std::string Setup[15];

int main(int argc, char* args[]){
    std::string tmpLine;
    std::ifstream TestData;
    int i = 0;
    std::cout << args[1] << std::endl << args[2];
    //Import Data 
    TestData.open("./setup.txt");
    try{
        while( std::getline(TestData, tmpLine) ){
            Setup[i] = tmpLine;
            i++;
        }
    }
    catch (int exp) {
        std::cout << "Error With Test Data File";
        return 1;
    }
    
    //Run Check
    if(!HasSafeState(Setup)){
        std::cout << std::endl << "The State is Unsafe." << std::endl;
        return 1;
    } else {
        std::cout << std::endl << "The State is Safe." << std::endl;
    }   

    //Get Data
    int * Max = GetMax(Setup);
    int * Allocation = GetAllocation(Setup);
    int * Available = GetAvailable(Setup);


    //Get CMD Line argument

    //Switch-Case for CMD Line Arg
        //Manual
            //the user can request any I of J for K
            //the user can release anu I of J for K
            //the user can end the program

        //Automatic
            //create 1 thread for each n process 
            //each thread generates 3 random requests and 3 release commands for itself
            //requests alternate with releases
            //after the requests and releases are done, terminate the thread
            //terminate the program after all threads are done

        //Base
            //Quit

}

