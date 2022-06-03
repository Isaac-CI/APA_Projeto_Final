#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"


int main(void){

    JobXServer instance = JobXServer("./input.txt");
    
    Greedy guloso = Greedy(instance);
   
    return 0;
}
