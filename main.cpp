#include <iostream>
#include <fstream>
#include <string>

static std::string Setup[15];

int main(){
    std::string tmpLine;
    std::ifstream TestData;
    int i = 0;

    TestData.open("./Data/setup.txt");
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
    std::cout << Setup[0];
}
//Import Data

//Init Data

//Run Check

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