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
       for(int i = 0; i < PROCESSES; i++){
              int* tmp = GetNum(6+PROCESSES, data);
              for(int j = 0; j < RESOURCES; j++){
                     Allocation[i*RESOURCES + j] = tmp[j];
              }
       }

       return Allocation;
}

int* GetMax(std::string data[]){
       int * Max = new int [PROCESSES*RESOURCES];
       std::cout << std::endl;
       //init max
       int* tmp;
       for(int i = 0; i < PROCESSES; i++){
              tmp = GetNum(i+5, data);
              std::cout << std::endl << tmp[0] << "_" <<tmp[1] <<"_" << tmp[2]<< std::endl ;
              for(int j = 0; j < RESOURCES; j++){
                     if(i == 4){
                            std::cout << std::endl << tmp[0] << "_" <<tmp[1] <<"_" << tmp[2]<< std::endl;
                     }
                     Max[i*RESOURCES + j] = tmp[j];
              }
              if(i == 4){
                     std::cout << std::endl<< "--------> " <<  Max[9]  << "_" << Max[10]  <<"_" <<  Max[11] << std::endl;
              }
       }
       std::cout << "\n--- MAX Array ---\n";
        for(int i = 0; i < PROCESSES; i++){
              tmp = GetNum(i+5, data);
              for(int j = 0; j < RESOURCES; j++){
                     std::cout << Max[i*RESOURCES + j] << "     ";
              }
              std::cout << std::endl;
       }

       return Max;
}

int* GetAvailable(std::string data[]){

       int * Available = new int [RESOURCES];

       Available = GetNum(3,data);
       std::cout << std::endl;
       for(int i = 0; i < 3; i++){
              std::cout << " " << Available[i];
       }

       return Available;
}

int GetResources(std::string data[]){
       return (int)data[0][0] - 48;
}

int GetProcesses(std::string data[]){
       return (int)data[1][0] - 48;
}

int* GetNeed(std::string data[]){
       int * Need = new int[PROCESSES*RESOURCES];

       for(int i = 0; i < PROCESSES; i++){
              for(int j = 0; j < RESOURCES; j++){
                     Need[i*RESOURCES+j] = MAX[i*RESOURCES+j] - ALLOCATION[i*RESOURCES+j];
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
                     while(NEED[i*RESOURCES + tmp] <= Work[tmp] || tmp < RESOURCES){
                            tmp++;
                     }
                     if(tmp == RESOURCES){
                            for(int j = 0; j < RESOURCES; j++){
                                   Work[j] += ALLOCATION[i*RESOURCES + j];
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
       std::cout << "=======>>>>>" << AVAILABLE[2] << "<<<<======";
       NEED = GetNeed(data);
      
       std::cout << "\n--- Allocated Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << ALLOCATION[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }
       std::cout << "\n--- MAX Array ---\n";
       for(int p = 0; p < PROCESSES; p++){
              for(int R = 0; R < RESOURCES; R++){      
                     std::cout << MAX[p*RESOURCES + R] << "     ";
              }
              std::cout << std::endl;
       }

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