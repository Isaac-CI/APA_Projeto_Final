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
                        + data.T[i][solution.servers[j].jobs[l].id - 1];
                    newTimeServerJ = solution.timeSpentPerServer[j] - solution.servers[j].jobs[l].tempo 
                        + data.T[j][solution.servers[i].jobs[k].id - 1];

                    if(newTimeServerI < data.b[i] && newTimeServerJ < data.b[j]){
                        newCostI = data.C[i][solution.servers[j].jobs[l].id - 1] - data.C[i][solution.servers[i].jobs[k].id - 1];
                        newCostJ = data.C[j][solution.servers[i].jobs[k].id - 1] - data.C[j][solution.servers[j].jobs[l].id - 1];
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
        Jobs aux1 = Jobs(solution.servers[newIndexJ].jobs[newIndexL].id, data.T[solution.servers[newIndexI].id - 1][solution.servers[newIndexJ].jobs[newIndexL].id - 1],
            data.C[solution.servers[newIndexI].id - 1][solution.servers[newIndexJ].jobs[newIndexL].id - 1], solution.servers[newIndexI].id);

        Jobs aux2 = Jobs(solution.servers[newIndexI].jobs[newIndexK].id, data.T[solution.servers[newIndexJ].id - 1][solution.servers[newIndexI].jobs[newIndexK].id - 1],
            data.C[solution.servers[newIndexJ].id - 1][solution.servers[newIndexI].jobs[newIndexK].id - 1], solution.servers[newIndexJ].id);

        
        solution.servers[newIndexI].jobs[newIndexK] = aux1;
        solution.servers[newIndexJ].jobs[newIndexL] = aux2;
        

        solution.solutionCost = newBestTotalCost;
        solution.servers[newIndexI].custoParaServidor = newBestCostI;
        solution.servers[newIndexJ].custoParaServidor = newBestCostJ;
        solution.timeSpentPerServer[newIndexI] = newBestCostTimeServerI;
        solution.timeSpentPerServer[newIndexJ] = newBestCostTimeServerJ;

        //std::cout << "Custo após o swap: " << solution.solutionCost << std::endl;

    }

    return solution;
}

Solution Vnd::reInsertionJob(Solution solution, JobXServer data, bool* betterSolutionFound){
    int bestCost = solution.solutionCost;
    int newCost;
    *betterSolutionFound = false;

    std::vector<Jobs> allJobs;

    for(int i = 0 ; i < data.m; i++){
        allJobs.insert(allJobs.end(), solution.servers[i].jobs.begin(), solution.servers[i].jobs.end());
    }

    allJobs.insert(allJobs.end(), solution.nonAllocatedJobs.begin(), solution.nonAllocatedJobs.end());

    
    int newindexServer, choosedJobindex, newCostAtServer;
    bool found = false;
    for(int i = 0; i < allJobs.size(); i ++){
        for(int j = 0; j < data.m; j++){
            if((solution.timeSpentPerServer[j] + data.T[j][allJobs[i].id - 1]) <= data.b[solution.servers[j].id - 1]){ // checa se cabe
                newCost = solution.solutionCost - allJobs[i].custo + data.C[j][allJobs[i].id - 1];
                
                if( newCost < bestCost){
                    newindexServer = j;
                    choosedJobindex = i;
                    newCostAtServer = data.T[j][allJobs[i].id - 1];
                    bestCost = newCost;
                    found = true;
                    // std::cout<< solution.solutionCost << " - " << allJobs[i].custo << "+" << + data.C[j][allJobs[i].id - 1] << " = " <<solution.solutionCost - allJobs[i].custo + data.C[j][allJobs[i].id - 1] << std::endl;
                }
            }
        }
    }

    Jobs choosedJob = allJobs[choosedJobindex];
    std::cout << choosedJob.id << std::endl;

    if(found){
        if(choosedJob.idServerAlloc == -1){
            choosedJob.idServerAlloc = newindexServer + 1;
            choosedJob.custo = newCostAtServer;
            solution.solutionCost = bestCost;
            solution.timeSpentPerServer[newindexServer] += choosedJob.custo;
            solution.servers[newindexServer].jobs.push_back(choosedJob);
            //solution.nonAllocatedJobs.erase(solution.nonAllocatedJobs.begin() + choosedJob.id - 1); // remove 

        }else{

        }
    }

    
    return solution;
}