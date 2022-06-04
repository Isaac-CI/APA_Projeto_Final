#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"


int main(void){

    JobXServer instance = JobXServer("./input2.txt");
    Solution* solution = (Solution*) std::calloc(1, sizeof(Solution));

    instance.printProblemInput();
    
    Greedy guloso = Greedy(instance, solution);
   
    return 0;
}
