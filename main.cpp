#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"


int main(void){

    JobXServer instance = JobXServer("./input2.txt");  

    instance.printProblemInput();
    
    Greedy guloso = Greedy(instance);
   
    return 0;
}
