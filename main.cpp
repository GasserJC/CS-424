#include <iostream>
#include <fstream>
#include "detect.hpp"
#include "banker.hpp"

/*
!!! !!!
 !!! !!!
  !!! !!!

    File Purposes:
            banker.hpp      =>  Contains all the resource and threading.
            detect.hpp      =>  Safe State Testing.
            Rando.hpp       =>  A File with thread safe Random Number Generator.
            Semaphore.hpp   =>  Mutex Locking.
            setup.txt       =>  Input with specific structure for resource/process state.
            main.cpp        =>  main abstraction of program.

  !!! !!!
 !!! !!!
!!! !!!
*/

static std::string Setup[15];

int main(int argc, char* args[]){
    try{
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
                TestData.open("./test2.txt");
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
        try{
            if(!HasSafeState(Setup)){
                std::cout << std::endl << "The State is Unsafe." << std::endl;
                return 1;
            } else {
                std::cout << std::endl << "The State is Safe." << std::endl;
            }   
        } catch (int exp) {
            std::cout << std::endl << "The State is Unsafe." << std::endl;
            return -1;
        }

        //Get Data
        MAX = GetMax(Setup);
        ALLOCATION = GetAllocation(Setup);
        AVAILABLE = GetAvailable(Setup);
        RESOURCES = GetResources(Setup);
        PROCESSES = GetProcesses(Setup);
        NEED = GetNeed(Setup);
        int method = 0;


        std::cout << Type;

        //Account for user choice
        if(Type == "manual" || Type == "Manual"){
            method = 1;
        } 
        else if(Type == "Automatic" || Type == "Auto" || Type == "auto" || Type == "automatic"){
            method = 2;
        }

        //Start simulation
        switch (method) {

            case 1:
                Manual();
                print();
                std::cout << std::endl << "Manual" << std::endl;
                break;

            case 2:
                Auto();
                print();
                std::cout << std::endl << "Automatic" << std::endl; 
                break;

            default:
                std::cout << std::endl << "Incorrect method type, enter (auto, or manual)" << std::endl;
        }
    } catch (...) {
        std::cout << std::endl << "Program Errored Out! (likely file path was incorrect)"  << std::endl;
        return -1;
    }
}

