#ifndef DETECT
#define DETECT
#include <string>

/*
def HasSafeState():
   For each process p in each resource R
           if( not (Allocation[p][R] <= Max[p][R]))
                  return false
           if( not (Sum(Allocation[R]  row) + Available[R] == [Total[R]] ))
                  return false               
   return true
*/

bool HasSafeState(std::string data[]){
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       std::cout << std::endl << "resources: " << resources << std::endl;
       std::cout << std::endl << "processes: " << processes << std::endl;
       return true;
}

#endif