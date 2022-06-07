#include "../interfaces/Vnd.h"
#include <algorithm>

Vnd::Vnd(Solution solution, JobXServer data){
    this->solution = solution;
    this->data = data;
}

Solution Vnd::swapServer(Solution solution, JobXServer data, bool* betterSolutionFound){
    int newBestCostTimeServerI, newBestCostTimeServerJ,newTotalCost, newBestTotalCost = solution.solutionCost, newBestCostI, newBestCostJ;
    int newIndexK, newIndexL, newCostI, newCostJ, newIndexI, newIndexJ, newTimeServerI, newTimeServerJ;
    *betterSolutionFound = false;

    for(unsigned int i = 0; i < data.m; i++){//worst case: Theta(n * m²) best case: Theta(n²)
        for(unsigned int j = i + 1; j < data.m; j++){
            for(unsigned int k = 0; k < solution.servers[i].jobs.size(); k++){
                for(unsigned int l = 0; l < solution.servers[j].jobs.size(); l++){
                    newTimeServerI = solution.timeSpentPerServer[i] - solution.servers[i].jobs[k].tempo 
                        + data.T[i][solution.servers[j].jobs[l].id];
                    newTimeServerJ = solution.timeSpentPerServer[j] - solution.servers[j].jobs[l].tempo 
                        + data.T[j][solution.servers[i].jobs[k].id];

                    if(newTimeServerI < data.b[i] && newTimeServerJ < data.b[j]){
                        newCostI = data.C[i][solution.servers[j].jobs[l].id] - data.C[i][solution.servers[i].jobs[k].id];
                        newCostJ = data.C[j][solution.servers[i].jobs[k].id] - data.C[j][solution.servers[j].jobs[l].id];
                        newTotalCost = solution.solutionCost + newCostI + newCostJ;
                        
                        if(newTotalCost < newBestTotalCost){
                            *betterSolutionFound = true;
                            newBestTotalCost = newTotalCost;
                            newBestCostI = solution.servers[i].custoParaServidor + newCostI;
                            newBestCostJ = solution.servers[j].custoParaServidor + newCostJ;
                            newBestCostTimeServerI = newTimeServerI;
                            newBestCostTimeServerJ = newTimeServerJ;
                            newIndexI = i;
                            newIndexJ = j;
                            newIndexK = k;
                            newIndexL = l;
                        }
                    }
                }
            
            }
        
        }
    
    }
    if(*betterSolutionFound){
        //swap solution[I][K] for solution[J][L]
        Jobs aux = Jobs(solution.servers[newIndexJ].jobs[newIndexL].id, solution.servers[newIndexJ].jobs[newIndexL].tempo,
            solution.servers[newIndexJ].jobs[newIndexL].custo);
        solution.servers[newIndexJ].jobs[newIndexL] = solution.servers[newIndexI].jobs[newIndexK];
        solution.servers[newIndexI].jobs[newIndexK] = aux;
        //

        solution.solutionCost = newBestTotalCost;
        solution.servers[newIndexI].custoParaServidor = newBestCostI;
        solution.servers[newIndexJ].custoParaServidor = newBestCostJ;
        solution.timeSpentPerServer[newIndexI] = newBestCostTimeServerI;
        solution.timeSpentPerServer[newIndexJ] = newBestCostTimeServerJ;

        std::cout << "Custo após o swap: " << solution.solutionCost << std::endl;

    }

    return solution;
}