#ifndef DETECT
#define DETECT
#include <string>
#include <vector>

//returns int array of a text file deliminated by spaces.
int * TextToIntArr(int line, int width, std::string data[]){
       int * returnArr = new int[width];
       std::string tmp = "";
       int i = 0, num = 0;
       
       //get data, and only grab numbers (not spaces or null)
       while(num < width){
              if(data[line][i] != ' ' && ( data[line][i] != '\0')){
                     tmp += data[line][i];
                     i++;
              } else {
                     //if space Therefore another number ahead.
                     //therefore, store current and proceed.
                     if(data[line][i] == ' '){ 
                            returnArr[num] = std::stoi(tmp);
                            tmp="";
                            i++; 
                            num++;
                     } else {  //assume end of line.
                            returnArr[num] = std::stoi(tmp);
                            break; 
                     }
              }
       }
       return returnArr;
}

/*
func HasSafeState():

   getData

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
              int* tmp = TextToIntArr(i+5,resources, data);
              for(int j = 0; j < resources; j++){
                     Max[i*resources + j] = tmp[j];
              }
       }

       //init allocation
       for(int i = 0; i < processes; i++){
              int* tmp = TextToIntArr(6+processes,resources, data);
              for(int j = 0; j < resources; j++){
                     Allocation[i*resources + j] = tmp[j];
              }
       }

       //init Available
       Available = TextToIntArr(3,resources,data);

       //Perform Check
       for(int p = 0; p < processes; p++){
              for(int R = 0; R < resources; R++){
                     if(Allocation[p*processes + R] > Max[p*processes + R]){
                            return false;
                     }
              }
       }
                 
       for(int R = 0; R < resources; R++){
              int sum = 0;
              for(int p = 0; p < processes; p++){
                     sum += Allocation[p*processes + R];
              }
              sum += Available[R];
              if(sum != Available[R]){
                     return false;
              }
       }

       return true;
}

int* GetAllocation(std::string data[]){
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       int * Allocation = new int [processes*resources];

       //init allocation
       for(int i = 0; i < processes; i++){
              int* tmp = TextToIntArr(6+processes,resources, data);
              for(int j = 0; j < resources; j++){
                     Allocation[i*resources + j] = tmp[j];
              }
       }

       return Allocation;
}

int* GetMax(std::string data[]){
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       int * Max = new int [processes*resources];

       //init max
       for(int i = 0; i < processes; i++){
              int* tmp = TextToIntArr(i+5,resources, data);
              for(int j = 0; j < resources; j++){
                     Max[i*resources + j] = tmp[j];
              }
       }

       return Max;
}

int* GetAvailable(std::string data[]){
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       int * Available = new int [processes*resources];

       Available = TextToIntArr(3,resources,data);

       return Available;
}

int GetResources(std::string data[]){
       return (int)data[0][0] - 48;
}

int GetProcesses(std::string data[]){
       return (int)data[1][0] - 48;
}

int* GetNeed(std::string data[]){
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       int * Max = GetMax(data);
       int * Allocation = GetAllocation(data);
       int * Need = new int[processes*resources];

       for(int i = 0; i < processes; i++){
              for(int j = 0; j < resources; j++){
                     Need[i*processes+j] = Max[i*processes+j] - Allocation[i*processes+j];
              }
       }

       return Need;
}

bool HasSafeState(){
       //Perform Check
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){
                     if(ALLOCATION[p*PROCESSES + R] > MAX[p*PROCESSES + R]){
                            return false;
                     }
              }
       }
       for(int R = 0; R < RESOURCES; R++){
              int sum = 0;
              for(int p = 0; p < PROCESSES; p++){
                     sum += ALLOCATION[p*PROCESSES + R];
              }
              sum += AVAILABLE[R];
              if(sum != AVAILABLE[R]){
                     return false;
              }
       }

       return true;
}

#endif