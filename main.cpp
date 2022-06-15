#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"
#include "./classes/interfaces/Vnd.h"


int main(void){
    JobXServer instance = JobXServer("./instances/input7.txt");  

    //instance.printProblemInput();
    Greedy guloso = Greedy(instance);
    std::cout << "Greedy Solution" << std::endl;

    std::cout <<"Custo total da solução do Greedy: " << guloso.solution.solutionCost << std::endl;

    for(int i = 0; i <  guloso.solution.servers.size(); i++){
        std::cout << "IDs dos jobs alocados no server" << guloso.solution.servers[i].id << " :";
        for(int j = 0; j < guloso.solution.servers[i].jobs.size(); j++){
            std::cout <<  guloso.solution.servers[i].jobs[j].id << " ";
        }
            std::cout << "Custo total do servidor: " << guloso.solution.servers[i].custoParaServidor << " ";
            std::cout << "\n";
    } 

    std::cout << "Id dos jobs nao alocados:";
    for(int i = 0; i <  guloso.solution.nonAllocatedJobs.size(); i++){
        std::cout <<  " " << guloso.solution.nonAllocatedJobs[i].id;
    }
    std::cout << "\n";

    //-------------------------------- VND ---------------------------------------
    Vnd VND = Vnd(guloso.solution, guloso.data);

        std::cout << "Solução alcançada pelo VND" << std::endl;
        int total = 0;
        for(int i = 0; i <  VND.solution.servers.size(); i++){
            std::cout << "IDs dos jobs alocados no server" << VND.solution.servers[i].id << " :";
            int time = 0;
            for(int j = 0; j < VND.solution.servers[i].jobs.size(); j++){
                std::cout << "Id: " <<   VND.solution.servers[i].jobs[j].id << " (tempo pratico: " << VND.solution.servers[i].jobs[j].tempo << ")"
                << " Tempo teorico: " << instance.T[VND.solution.servers[i].id -1][ VND.solution.servers[i].jobs[j].id - 1] << " ";
                time += VND.solution.servers[i].jobs[j].tempo;
            }
            std::cout << " Tempo teorico para o servidor : " << time << " Tempo maximo para o servidor: " << instance.b[VND.solution.servers[i].id -1];
            std::cout << "\n";
        }

        std::cout << "Id dos jobs nao alocados:";
        for(int i = 0; i <  VND.solution.nonAllocatedJobs.size(); i++){
            std::cout <<  " " << VND.solution.nonAllocatedJobs[i].id;
        }
        
        std::cout << "\n";
        std::cout <<"Custo total da solução do VND: " << VND.solution.solutionCost << std::endl;

    return 0;
}
