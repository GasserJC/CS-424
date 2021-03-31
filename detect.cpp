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


int * TextToIntArr(int line, int width, std::string data[]){
       int * returnArr = new int[width];
       std::string tmp = "";
       int i = 0, num = 0;
       
       //get data, and only grab numbers (not spaces or null)
       while(num < width){
              if(data[line][i] != ' ' && ( data[line][i] == '\0')){
                     tmp += data[line][i];
                     i++;
              } else {
                     //if space Therefore another number ahead.
                     //therefore, store current and proceed.
                     if(data[line][i] != ' '){ 
                            returnArr[num] = std::stoi(tmp);
                            i++; 
                            num++;
                     } else {  //assume end of line.
                            break; 
                     }
              }
       }

       return returnArr;
}

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

       Available = TextToIntArr(3,3,data);

       for(int i = 0; i < resources; i++){
              std::cout << std::endl << data[11][900];
       }
       return true;
}


#endif