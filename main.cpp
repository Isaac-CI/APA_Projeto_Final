#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"
#include "./classes/interfaces/Vnd.h"


int main(void){
    bool flag = true;
    JobXServer instance = JobXServer("./instances/input2.txt");  

    //instance.printProblemInput();
    
    Greedy guloso = Greedy(instance);

    std::cout << "Greedy Solution" << std::endl;

    std::cout <<"Custo total da solução do Greedy: " << guloso.solution.solutionCost << std::endl;

    for(int i = 0; i <  guloso.solution.servers.size(); i++){
        std::cout << "IDs dos jobs alocados no server" << guloso.solution.servers[i].id << " :";
        for(int j = 0; j < guloso.solution.servers[i].jobs.size(); j++){
            std::cout <<  guloso.solution.servers[i].jobs[j].idServerAlloc << " ";
        }
            std::cout << "\n";
    } 

    std::cout << "Id dos jobs nao alocados:";
    for(int i = 0; i <  guloso.solution.nonAllocatedJobs.size(); i++){
        std::cout <<  " " << guloso.solution.nonAllocatedJobs[i].id;
    }
    std::cout << "\n";

    //-------------------------------- VND ---------------------------------------
    Vnd VND = Vnd(guloso.solution, instance);
    while(flag){
        VND.solution = VND.swapServer(VND.solution, instance, &flag);
    }

    std::cout << "VND Solution" << std::endl;
    
    std::cout <<"Custo total da solução do VND (Swaps only): " << VND.solution.solutionCost << std::endl;
  
    for(int i = 0; i <  VND.solution.servers.size(); i++){
        std::cout << "IDs dos jobs alocados no server" << VND.solution.servers[i].id << " :";
        for(int j = 0; j < VND.solution.servers[i].jobs.size(); j++){
            std::cout <<  VND.solution.servers[i].jobs[j].idServerAlloc << " ";
        }
         std::cout << "\n";
    }

    std::cout << "Id dos jobs nao alocados:";
    for(int i = 0; i <  VND.solution.nonAllocatedJobs.size(); i++){
        std::cout <<  " " << VND.solution.nonAllocatedJobs[i].id;
    }
    std::cout << "\n";
    
    return 0;
}
