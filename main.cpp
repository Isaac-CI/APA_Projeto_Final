#include <iostream>
#include <vector>
#include <string.h>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"
#include "./classes/interfaces/Vnd.h"
#include "./classes/interfaces/Grasp.h"
#include "./classes/interfaces/Gap.h"

#define THRESHOLD 10
#define INSTANCE 7

int main(void){
    JobXServer instance = JobXServer("./instances/input7.txt");  

    auto greedStart = std::chrono::high_resolution_clock::now();
    Greedy guloso = Greedy(instance);
    auto greedFinish = std::chrono::high_resolution_clock::now();
    auto greedDuration = std::chrono::duration_cast<std::chrono::microseconds>(greedFinish - greedStart);
    std::cout << "Solução Gulosa encontrada em "<< greedDuration.count() << " us: " << std::endl;

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
    std::cout << "\n";

    //-------------------------------- VND ---------------------------------------
    Vnd VND = Vnd(guloso.solution, guloso.data);

        std::cout << "Solução alcançada pelo VND em " << VND.executionTime.count() << " us: " << std::endl;
        for(int i = 0; i <  VND.solution.servers.size(); i++){
            std::cout << "IDs dos jobs alocados no server" << VND.solution.servers[i].id << " :";
            int time = 0;
            for(int j = 0; j < VND.solution.servers[i].jobs.size(); j++){
                std::cout <<   VND.solution.servers[i].jobs[j].id << " ";
                time += VND.solution.servers[i].jobs[j].tempo;
            }
            std::cout << " Custo para o servidor: " << VND.solution.servers[VND.solution.servers[i].id -1].custoParaServidor;
            std::cout << "\n";
        }

        std::cout << "Id dos jobs nao alocados:";
        for(int i = 0; i <  VND.solution.nonAllocatedJobs.size(); i++){
            std::cout <<  " " << VND.solution.nonAllocatedJobs[i].id;
        }
        
        std::cout << "\n";
        std::cout <<"Custo total da solução do VND: " << VND.solution.solutionCost << std::endl;
        std::cout << "\n";

        int lastIterWithBetterSolution = 0;
        int currentIter = 0;
        Solution best = VND.solution;
        auto startGrasp =  std::chrono::high_resolution_clock::now();
        while(currentIter - lastIterWithBetterSolution < THRESHOLD){    
            Grasp arrochado = Grasp(instance);
            Vnd graspVND = Vnd(arrochado.solution, instance);
            if(graspVND.solution.solutionCost < best.solutionCost){
                lastIterWithBetterSolution = currentIter;
                best = graspVND.solution;
            }
            currentIter++;
        }
        auto stopGrasp = std::chrono::high_resolution_clock::now();
        auto GraspDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopGrasp - startGrasp);
        std::cout << "Solução alcançada pelo grasp VND em " << GraspDuration.count() << " us: " << std::endl;
        for(int i = 0; i <  best.servers.size(); i++){
            std::cout << "IDs dos jobs alocados no server" << best.servers[i].id << " :";
            int time = 0;
            for(int j = 0; j < best.servers[i].jobs.size(); j++){
                std::cout << best.servers[i].jobs[j].id << " ";
                time += best.servers[i].jobs[j].tempo;
            }
            std::cout << " Custo para o servidor: " << best.servers[best.servers[i].id -1].custoParaServidor;
            std::cout << "\n";
        }

        std::cout << "Id dos jobs nao alocados:";
        for(int i = 0; i <  best.nonAllocatedJobs.size(); i++){
            std::cout <<  " " << best.nonAllocatedJobs[i].id;
        }
        
        std::cout << "\n";
        std::cout <<"Custo total da solução do graspVND: " << best.solutionCost << std::endl;
        std::cout << "\n";

        Gap gap = Gap(VND.solution, INSTANCE);
        gap.printGap();

    return 0;
}
