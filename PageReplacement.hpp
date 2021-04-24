#ifndef PAGE
#define PAGE

static const int LEFT = 1;
static const int RIGHT = 6;
static const int REF_SIZE = 20;
static const int REF_AMP = 10;

void PrintArr(int arr[], int n){
    std::cout << " [ ";
    for(int i = 0; i < n; i++){
        std::cout << arr[i];
        if(i < n - 1){
            std::cout << " , ";
        } else {
            std::cout << " ]\n";
        }
    }
}

bool HasRefChar(int Mem[], int Char, int FC){
    for(int i = 0; i < FC; i++){
        if(Mem[i] == Char){
            return true;
        }
    }
    return false;
}

int FindOldest(int Age[], int FC){
    int min = REF_SIZE + 1;
    int idx = 0;
    for(int i = 0; i < FC; i++){
        if(min > Age[i]){
            min = Age[i];
            idx = i;
        }
    }
    return idx;
}

int FindIndexOfValue(int arr[], int n, int val){
    for(int i = 0; i < n; i++){
        if(arr[i] == val){
            return i;
        }
    }
    return -1;
}

int FindStale(int mem[], int arr[], int fc, int t){
    int * tmp_mem = new int[fc];
    int count = 0;
    for(int i = 0; i < fc; i++) {tmp_mem[i] = mem[i];} 

    for(int i = t; i < REF_SIZE; i++){
        for(int j = 0; j < fc; j++){
            if(tmp_mem[j] == arr[i]){
                tmp_mem[j] = -1;
                count++;
                break;
            }
        }
        if(count + 1 == fc){ //Case : all things in memory are in the ref still
            for(int j = 0; j < fc; j++){
                if(tmp_mem[j] != -1){
                    PrintArr(tmp_mem, fc);
                    return j;
                }
            }
        }
    }

    for(int j = 0; j < fc; j++){ // Case: there exist items in mem that are no longer in ref
        if(tmp_mem[j] != -1){
            PrintArr(tmp_mem, fc);
            return j;
        }
    }
    PrintArr(tmp_mem, fc);
    return 0; //Case: none of the mem items are in ref again
}

//First In First Out Algorithm
void FIFO(int arr[], int FC){

    int Faults = 0;
    int * Memory = new int[FC]; 
    int * Age = new int [FC];
    for(int i = 0; i < FC; i++){ Memory[i] = -1; Age[i] = -1;}

    for(int i = 0; i < REF_SIZE; i++){ 

        if(!HasRefChar(Memory, arr[i], FC)){        // If Page Fault
            Faults++;                               // Add to Faults
            int First = FindOldest(Age, FC);        // Find the first in
            Memory[First] = arr[i];                 // Re-assign first in
            Age[First] = i;                         // Update age
        }
    }

    std::cout << "FIFO had " << Faults << " many Page Faults" << std::endl;

}

//Least Recently Used Algorithm
void LRU(int arr[], int FC){
    
    int Faults = 0;
    int * Memory = new int[FC];
    int * Age = new int [FC];
    for(int i = 0; i < FC; i++){ Memory[i] = -1; Age[i] = -1;}

    for(int i = 0; i < REF_SIZE; i++){ 
        if(!HasRefChar(Memory, arr[i], FC)){         // If Page Fault
            Faults++;                            // Add to Faults
            int OldestUsed = FindOldest(Age, FC);// Find the last used
            Memory[OldestUsed] = arr[i];                  // Re-assign first in
            Age[OldestUsed] = i;                          // Update age
        } 
        else {                                   // If not page fault
            int idx = FindIndexOfValue(Memory, FC, arr[i]);
            Age[idx] = i;                          //updating this changes the algo from fifo to lru
        }
    }

    std::cout << "LRU had " << Faults << " many Page Faults" << std::endl;
}

//Optimal Algorithm
void OPT(int arr[], int FC){
    
    int Faults = 0;
    int * Memory = new int[FC];
    for(int i = 0; i < FC; i++){ Memory[i] = -1;}

    for(int i = 0; i < REF_SIZE; i++){ 
        if(!HasRefChar(Memory, arr[i], FC)){     // If Page Fault
            Faults++;                            // Add to Faults
            if(HasRefChar(Memory, -1, FC)){
                Memory[FindIndexOfValue(Memory, FC, -1)] = arr[i];
            } else {
                int StaleIdx = FindStale(Memory, arr, FC, i);
                Memory[StaleIdx] = arr[i];
            }
        } 
    }

    std::cout << "Optimal had " << Faults << " many Page Faults" << std::endl;
}

#endif