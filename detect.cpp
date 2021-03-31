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
       //init resources and processes
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       int * Max = new int [processes*resources];
       int * Allocation = new int [processes*resources];
       int * Available = new int [resources];

       //init max
       for(int i = 0; i < processes; i++){
              for(int j = 0; j < resources; j++){
                     Max[i*resources + j] = (int)data[5+i][2*j] - 48;
              }
       }

       //init allocation
       for(int i = 0; i < processes; i++){
              for(int j = 0; j < resources; j++){
                     Allocation[i*resources + j] = (int)data[11+i][2*j] - 48;
              }
       }

       //init available
       for(int i = 0; i < resources; i++){
              Available[2*i] = (int)data[3][i] - 48;
       }

       for(int i = 0; i < resources; i++){
              std::cout << std::endl << Available[2*i];
       }
       return true;
}

#endif