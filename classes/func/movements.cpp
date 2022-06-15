#include "../interfaces/movements.h"
#include <algorithm>

Movements::Movements(Solution solution, JobXServer data){
    this->solution = solution;
    this->data = data;
}

std::vector<Jobs> removeJob(std::vector<Jobs> jobs, int id){
    for(int i = 0; i < jobs.size(); i++){
        if(jobs[i].id == id){
            jobs.erase(jobs.begin()+ i);
        }
    }
    return jobs;
}

Solution Movements::swapServer(Solution solution, JobXServer data, bool* betterSolutionFound){
    int newBestCostTimeServerI, newBestCostTimeServerJ,newTotalCost, newBestTotalCost = solution.solutionCost, newBestCostI, newBestCostJ;
    int newIndexK, newIndexL, newCostI, newCostJ, newIndexI, newIndexJ, newTimeServerI, newTimeServerJ;
    *betterSolutionFound = false;

    for(unsigned int i = 0; i < data.m; i++){//worst case: Theta(n * m²) avarage case: Theta(n²) best case: Omega(n)
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

Solution Movements::reInsertionJob(Solution solution, JobXServer data, bool* betterSolutionFound){
    int bestTotalCost = solution.solutionCost;
    int newTotalCost;
    *betterSolutionFound = false;
    int recievingServerIndex, recievingServerNewTime, recievingServerNewCost;
    int donorServerIndex, donorServerNewTime, donorServerNewCost;
    int choosenJobIndex, iterStart[data.m];
    int counter = 0;

    std::vector <Jobs> allocatedJobs;

    for(int i = 0; i < data.m; i++){
        iterStart[i] = counter;
        for(int j = 0; j < solution.servers[i].jobs.size(); j++){
            allocatedJobs.push_back(Jobs(solution.servers[i].jobs[j].id, solution.servers[i].jobs[j].tempo, solution.servers[i].jobs[j].custo, solution.servers[i].jobs[j].idServerAlloc));
            counter++;
        }
    }
    for(int j = 0; j < solution.nonAllocatedJobs.size(); j++){
        for(int i = 0; i < data.m; i++){
            if(solution.timeSpentPerServer[i] + data.T[i][solution.nonAllocatedJobs[j].id - 1] < data.b[i]){
                newTotalCost = solution.solutionCost + data.C[i][solution.nonAllocatedJobs[j].id - 1] - data.p;
                if(newTotalCost < bestTotalCost){
                    *betterSolutionFound = true;
                    bestTotalCost = newTotalCost;

                    recievingServerIndex = i;
                    donorServerIndex = -1;
                    choosenJobIndex = j;

                    recievingServerNewCost = solution.servers[i].custoParaServidor + data.C[i][solution.nonAllocatedJobs[j].id - 1];
                    recievingServerNewTime = solution.timeSpentPerServer[i] + data.T[i][solution.nonAllocatedJobs[j].id - 1];
                }
            }
        }
    }
    
    for(int j = 0; j < allocatedJobs.size(); j++){
        for(int i = 0; i < data.m; i++){
            if(solution.timeSpentPerServer[i] + data.T[i][allocatedJobs[j].id - 1] < data.b[i]){
                newTotalCost = solution.solutionCost - data.C[allocatedJobs[j].idServerAlloc - 1][allocatedJobs[j].id - 1]
                    + data.C[i][allocatedJobs[j].id - 1];
                if(newTotalCost < bestTotalCost){
                    *betterSolutionFound = true;
                    bestTotalCost = newTotalCost;

                    recievingServerIndex = i;
                    donorServerIndex = allocatedJobs[j].idServerAlloc - 1;
                    choosenJobIndex = j - iterStart[allocatedJobs[j].idServerAlloc - 1];

                    recievingServerNewCost = solution.servers[i].custoParaServidor + data.C[i][allocatedJobs[j].id - 1];
                    donorServerNewCost = solution.servers[donorServerIndex].custoParaServidor
                        - data.C[donorServerIndex][allocatedJobs[j].id - 1];

                    recievingServerNewTime = solution.timeSpentPerServer[i] + data.T[i][allocatedJobs[j].id - 1];
                    donorServerNewTime = solution.timeSpentPerServer[donorServerIndex] - data.T[donorServerIndex][allocatedJobs[j].id - 1];
                }
            }
        }
    }

    if(*betterSolutionFound){
        solution.solutionCost = bestTotalCost;
        solution.timeSpentPerServer[recievingServerIndex] = recievingServerNewTime;
        solution.servers[recievingServerIndex].custoParaServidor = recievingServerNewCost;
        solution.servers[recievingServerIndex].jobAmmount++;

        if(donorServerIndex < 0){
            solution.servers[recievingServerIndex].jobs.push_back(solution.nonAllocatedJobs[choosenJobIndex]);
            solution.servers[recievingServerIndex].jobs.back().idServerAlloc = recievingServerIndex + 1;
            solution.servers[recievingServerIndex].jobs.back().custo = data.C[recievingServerIndex][solution.servers[recievingServerIndex].jobs.back().id - 1];
            solution.servers[recievingServerIndex].jobs.back().tempo = data.T[recievingServerIndex][solution.servers[recievingServerIndex].jobs.back().id - 1];
            solution.nonAllocatedJobs.erase(solution.nonAllocatedJobs.begin() + choosenJobIndex);
        }else{
            solution.servers[recievingServerIndex].jobs.push_back(solution.servers[donorServerIndex].jobs[choosenJobIndex]);
            solution.timeSpentPerServer[donorServerIndex] = donorServerNewTime;
            solution.servers[donorServerIndex].custoParaServidor = donorServerNewCost;
            solution.servers[donorServerIndex].jobAmmount--;
            solution.servers[recievingServerIndex].jobs.back().idServerAlloc = recievingServerIndex + 1;
            solution.servers[recievingServerIndex].jobs.back().custo = data.C[recievingServerIndex][solution.servers[recievingServerIndex].jobs.back().id - 1];
            solution.servers[recievingServerIndex].jobs.back().tempo = data.T[recievingServerIndex][solution.servers[recievingServerIndex].jobs.back().id - 1];
            solution.servers[donorServerIndex].jobs.erase(solution.servers[donorServerIndex].jobs.begin() + choosenJobIndex);
        }
    }

    return solution;
}