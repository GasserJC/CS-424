#ifndef DETECT
#define DETECT
#include <string>
#include <vector>
#include <sstream>

static int * MAX;
static int * ALLOCATION;
static int * AVAILABLE;
static int * NEED;
static int RESOURCES;
static int PROCESSES;

int* GetNum(int line, std::string data[]){
       std::stringstream Stream(data[line]);
       std::vector<std::string> tmp;
       std::string Word;
       while(Stream >> Word){
              tmp.push_back(Word);
       }
       int * RtrArr = new int[tmp.size()];
       for(int i = 0; i < tmp.size() ; i++){
              RtrArr[i] = std::stoi(tmp[i]);
       }
       return RtrArr;
}

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


int* GetAllocation(std::string data[]){
       int resources = (int)data[0][0] - 48;
       int processes = (int)data[1][0] - 48;
       int * Allocation = new int [processes*resources];

       //init allocation
       for(int i = 0; i < processes; i++){
              int* tmp = GetNum(6+processes, data);
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
              int* tmp = GetNum(i+5, data);
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

       Available = GetNum(3,data);

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
       bool * Finished = new bool[PROCESSES];
       int * Work = new int[RESOURCES];
       bool Safe = false;
       
       for(int i = 0; i < PROCESSES; i++){
              Finished[i] = false;
       }
       for(int i = 0; i < RESOURCES; i++){
              Work[i] = AVAILABLE[i];
       }

       //static deadlock check
       for(int i = 0; i < PROCESSES; i++){
              if(!Finished[i]){
                     int tmp = 0;
                     while(NEED[i*PROCESSES + tmp] <= Work[tmp] || tmp < RESOURCES){
                            tmp++;
                     }
                     if(tmp == RESOURCES){
                            for(int j = 0; j < RESOURCES; j++){
                                   Work[j] += ALLOCATION[i*PROCESSES + j];
                            }
                            Finished[i] = true;
                            i--;
                     }
              }
       }

       int tmp = 0;
       while(Finished[tmp] != false || tmp < PROCESSES){
              tmp++;
       }
       if(PROCESSES == tmp){
              Safe = true;
       }

       delete[] Finished;
       delete[] Work;
       return Safe;
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
              int* tmp = GetNum(i+5, data);
              for(int j = 0; j < resources; j++){
                     Max[i*resources + j] = tmp[j];
                     std::cout << tmp[j];
              }
       }

       //init allocation
       for(int i = 0; i < processes; i++){
              int* tmp = GetNum(6+processes, data);
              for(int j = 0; j < resources; j++){
                     Allocation[i*resources + j] = tmp[j];
              }
       }

       //init Available
       Available = GetNum(3,data);
 
       std::cout << "\n--- Allocated Array ---\n";
       for(int p = 0; p < processes; p++){
              for(int R = 0; R < resources; R++){      
                     std::cout << Allocation[p*processes + R] << "     ";
              }
              std::cout << std::endl;
       }
       std::cout << "\n--- Max Array ---\n";
       for(int p = 0; p < processes; p++){
              for(int R = 0; R < resources; R++){      
                     std::cout << Allocation[p*processes + R] << "     ";
              }
              std::cout << std::endl;
       }

       //Perform Check
       for(int p = 0; p < processes; p++){
              for(int R = 0; R < resources; R++){
                     if(Allocation[p*processes + R] > Max[p*processes + R]){
                            
                            return false;
                     }
              }
       }
       return HasSafeState();
}

void print(){
       std::cout << "\n--- Max Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){
                     std::cout << MAX[p*PROCESSES + R] << "     ";
              }
              std::cout << std::endl;
       }

       std::cout << "\n--- Allocated Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << ALLOCATION[p*PROCESSES + R] << "     ";
              }
              std::cout << std::endl;
       }

       std::cout << "\n--- Available Array ---\n";

       for(int R = 0; R < RESOURCES; R++){      
              std::cout << AVAILABLE[R] << "     ";
       }

}

#endif