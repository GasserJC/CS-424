#include <iostream>
#include "PageReplacement.hpp"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int GetPageCount(){

    int tmp_page_frames;
    std::cout << "How many page frames are in the system? ";
    std::cin >> tmp_page_frames;

    if(tmp_page_frames < LEFT || tmp_page_frames > RIGHT){
        tmp_page_frames = -1;
    }

    return tmp_page_frames;

}

int * GetRandRef(){
    int* tmp = new int[REF_SIZE];
    srand(time(NULL));
    for(int i = 0; i < REF_SIZE; i++){
        tmp[i] = rand() % REF_AMP;
    }
    return tmp;
}


bool PageReplacement(){
    int FrameCount = 0;

    //Set Page Frame Count
    while(FrameCount == 0){
        FrameCount = GetPageCount();
    }

    if(!(FrameCount <= RIGHT && FrameCount >= LEFT)){
        FrameCount = LEFT;
    }

    std::cout << "made it here";
    
    //generate string with page numbers
    int * ReferenceString = GetRandRef();
    PrintArr(ReferenceString, REF_SIZE);
    
    //Display page faults using FIFO
    FIFO(ReferenceString, FrameCount);
    
    //Display page faults using LRU
    LRU(ReferenceString, FrameCount);
    /*
    //Display page faults using OPT
    OPT(ReferenceString, FrameCount);

    std::string tmp = "";
    std::cout <<std::endl << "Do you want do another iteration of the program? (y/n): ";
    std::cin >> tmp;

    if(tmp == "y" || tmp == "Y" || tmp == "yes" || tmp == "Yes"){
        return true;
    } else {
        return false;
    }
    */
   return true;
}

int main(){
    while(PageReplacement()){}
    return 1;
}