#include <iostream>
#include <vector>
#include "./classes/interfaces/JobXServer.h"
#include "./classes/interfaces/Greedy.h"
#include "./classes/interfaces/Vnd.h"
#include "./classes/interfaces/Grasp.h"

#define THRESHOLD 10

int main(void){
    srand(time(NULL));
    JobXServer instance = JobXServer("./instances/input8.txt");  

    auto greedStart = std::chrono::high_resolution_clock::now();
    Greedy guloso = Greedy(instance);
    auto greedFinish = std::chrono::high_resolution_clock::now();
    auto greedDuration = std::chrono::duration_cast<std::chrono::microseconds>(greedFinish - greedStart);
    std::cout << "Solução Gulosa encontrada em "<< greedDuration.count() << " us: " << std::endl;
    std::cout << "Custo do médio do Greedy: " << guloso.solution.solutionCost << std::endl;
    std::cout << "\n";

    //-------------------------------- VND ---------------------------------------
    Vnd VND = Vnd(guloso.solution, guloso.data);

        std::cout << "Solução alcançada pelo VND em " << VND.executionTime.count() << " us: " << std::endl;
        std::cout << "Custo do médio do  VND: " << VND.solution.solutionCost << std::endl;
        std::cout << "\n";


        int lastIterWithBetterSolution = 0;
        int currentIter = 0;
        Solution best = VND.solution;
        auto startGrasp =  std::chrono::high_resolution_clock::now();
        while(currentIter - lastIterWithBetterSolution < THRESHOLD){    
            Grasp arrochado = Grasp(instance);
            Vnd graspVND = Vnd(arrochado.solution, instance);
            std::cout << "Grasp " << currentIter << " cost: " << graspVND.solution.solutionCost << std::endl;
            std::cout << "\n";
            if(graspVND.solution.solutionCost < best.solutionCost){
                lastIterWithBetterSolution = currentIter;
                best = graspVND.solution;
            }
            currentIter++;
        }
        auto stopGrasp = std::chrono::high_resolution_clock::now();
        auto GraspDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopGrasp - startGrasp);
        std::cout << "Solução alcançada pelo grasp VND em " << GraspDuration.count() << " us: " << std::endl;
        std::cout << "Custo do médio do Grasp VND: " << best.solutionCost << std::endl;

    return 0;
}
