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
    srand(time(NULL));
    JobXServer instance = JobXServer("./instances/input2.txt");  

    auto greedStart = std::chrono::high_resolution_clock::now();
    Greedy guloso = Greedy(instance);
    auto greedFinish = std::chrono::high_resolution_clock::now();
    auto greedDuration = std::chrono::duration_cast<std::chrono::microseconds>(greedFinish - greedStart);
    std::cout << "Solução Gulosa encontrada em "<< greedDuration.count() << " us: " << std::endl;
    std::cout << "Custo da solução Gulosa: " << guloso.solution.solutionCost << std::endl;
    std::cout << "\n";

    //-------------------------------- VND ---------------------------------------
    Vnd VND = Vnd(guloso.solution, guloso.data);

        std::cout << "Solução alcançada pelo VND em " << VND.executionTime.count() << " us: " << std::endl;
        std::cout << "Melhor custo encontrado pelo VND: " << VND.solution.solutionCost << std::endl;
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
        std::cout << "Solução alcançada pelo Grasp + VND em " << GraspDuration.count() << " us: " << std::endl;
        std::cout << "Melhor custo encotrado pelo Grasp + VND: " << best.solutionCost << std::endl;

        Gap gap = Gap(VND.solution, INSTANCE);
        gap.printGap();

    return 0;
}
