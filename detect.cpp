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
       int * Max = new int [processes*resources];
       for(int i = 0; i < processes; i++){
              for(int j = 0; j < resources; j++){
                     int tmp = Max[i*resources + j] = (int)data[5+i][2*j] - 48;
              }
       }
       for(int i = 0; i < 15; i++){
              std::cout << std::endl << Max[i];
       }
       return true;
}

#endif