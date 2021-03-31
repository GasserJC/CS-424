#include <iostream>
#include <fstream>
#include "detect.cpp"

static std::string Setup[15];

int main(int argc, char* args[]){
    std::string tmpLine;
    std::ifstream TestData;
    int i = 0;

    //Get CMD Line argument
    std::string Type(args[1]);
    std::string FilePath(args[2]);

    //args[1] == manual or auto, args[2] == file input

    //Import Data 
    try{
        TestData.open("./" + FilePath);
    } catch (int exp) {
        std::cout << "your file does not exist, proceeding with default path/input - setup.txt";
        try{
            TestData.open("./setup.txt");
        } catch (int exp) {
            std::cout << "unable to find default file.";
            return -1;
        }
        
    }
    
    try{
        while( std::getline(TestData, tmpLine) ){
            Setup[i] = tmpLine;
            i++;
        }
    }
    catch (int exp) {
        std::cout << "Error With Test Data File";
        return -1;
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

