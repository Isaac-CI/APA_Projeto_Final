#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"
#include "./classes/interfaces/Vnd.h"


int main(void){
    bool flag = true;
    JobXServer instance = JobXServer("./instances/input7.txt");  

    instance.printProblemInput();
    
    Greedy guloso = Greedy(instance);
    Vnd VND = Vnd(guloso.solution, instance);
    while(flag){
        VND.solution = VND.swapServer(VND.solution, instance, &flag);
    }
    return 0;
}
