#ifndef DETECT
#define DETECT
#include <string>
#include <vector>

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
              Available[i] = (int)data[3][2*i] - 48;
       }

       for(int i = 0; i < resources; i++){
              std::cout << std::endl << data[11][900];
       }
       return true;
}


int * TextToIntArr(int start, int end, std::string data[]){
       for(int a = start; a <= end; a++){
              std::string tmp = "";
              int i = 0;
              while(true){
                     if(data[a][i] != ' ' && data[a][i] != ''){

                     } else {
                            break;
                     }
              }
       }
}
#endif