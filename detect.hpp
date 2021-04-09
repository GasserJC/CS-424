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

int* GetAllocation(std::string data[]){
       int * Allocation = new int [PROCESSES*RESOURCES];
       //init allocation
       int* tmp;
       for(int i = 0; i < PROCESSES; i++){
              tmp = GetNum(i+6+PROCESSES, data);
              for(int j = 0; j < RESOURCES; j++){
                     Allocation[i*RESOURCES + j] = tmp[j];
              }
       }
       return Allocation;
}

int* GetMax(std::string data[]){
       int * Max = new int [PROCESSES*RESOURCES];
       //init max
       int* tmp;
       for(int i = 0; i < PROCESSES; i++){
              tmp = GetNum(i+5, data);
              for(int j = 0; j < RESOURCES; j++){
                     Max[i*RESOURCES + j] = tmp[j];
              }

       }
       return Max;
}

int* GetAvailable(std::string data[]){
       int * Available = new int [RESOURCES];
       Available = GetNum(3,data);
       return Available;
}

int GetResources(std::string data[]){
       return (int)data[0][0] - 48;
}

int GetProcesses(std::string data[]){
       return (int)data[1][0] - 48;
}

int* GetNeed(){
       int * Need = new int[PROCESSES*RESOURCES];

       for(int i = 0; i < PROCESSES; i++){
              for(int j = 0; j < RESOURCES; j++){
                     Need[i*RESOURCES+j] = MAX[i*RESOURCES+j] - ALLOCATION[i*RESOURCES+j];
              }
       }

       return Need;
}

bool HasSafeState() {

bool safe = false;bool *finish = new bool[PROCESSES];int *work = new int[RESOURCES];

for(int i=0;i<PROCESSES;i++) { finish[i] = false; } 

for(int i=0;i<RESOURCES;i++) { work[i] = AVAILABLE[i]; }

for (int i=0;i<PROCESSES;i++) { if(finish[i] == false) { int tmp; for(tmp = 0; tmp < RESOURCES; tmp++) { if(NEED[i*RESOURCES + tmp] > work[tmp]) { break; } } if(tmp == RESOURCES) { for(int j=0;j<RESOURCES;j++) { work[j] += ALLOCATION[i*RESOURCES + j]; } finish[i] = true; i--; } }}

int tmp = 0;

for(tmp=0;tmp<PROCESSES;tmp++) { if(finish[tmp] == false) {break;}}

if(tmp == PROCESSES) { safe = true; }

delete[] finish;

delete[] work;

return safe;

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
       RESOURCES = (int)data[0][0] - 48;
       PROCESSES = (int)data[1][0] - 48;
       MAX = GetMax(data);
       ALLOCATION = GetAllocation(data);
       AVAILABLE = GetAvailable(data);
       NEED = GetNeed();
      
       std::cout << "\n--- Starting Allocated Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << ALLOCATION[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }
       std::cout << "\n--- Starting MAX Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << MAX[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }
       std::cout << "\n--- Starting Available Array ---\n";
       for(int R = 0; R < RESOURCES; R++){      
              std::cout << AVAILABLE[R] << "     ";
       }
       std::cout << std::endl;

       std::cout << "\n--- Starting Need Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << NEED[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }
       std::cout << std::endl;


       //Perform Check
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){
                     if(ALLOCATION[p*RESOURCES + R] > MAX[p*RESOURCES + R]){
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
                     std::cout << MAX[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }

       std::cout << "\n--- Allocated Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << ALLOCATION[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }

       std::cout << "\n--- Available Array ---\n";

       for(int R = 0; R < RESOURCES; R++){      
              std::cout << AVAILABLE[R] << "     ";
       }

}

#endif