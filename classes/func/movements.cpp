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

Solution Movements::reInsertionJob(Solution solution, JobXServer data, bool* betterSolutionFound){
    int bestCost = solution.solutionCost;
    int newCost;
    *betterSolutionFound = false;

    std::vector<Jobs> allJobs;

    for(int i = 0 ; i < data.m; i++){
        allJobs.insert(allJobs.end(), solution.servers[i].jobs.begin(), solution.servers[i].jobs.end());
    }

    allJobs.insert(allJobs.end(), solution.nonAllocatedJobs.begin(), solution.nonAllocatedJobs.end());

    
    int newindexServer, choosedJobindex, newtimeAtServer, costAtServer;
    bool found = false;
    Jobs choosedJob = Jobs();
    for(int i = 0; i < allJobs.size(); i ++){
        for(int j = 0; j < data.m; j++){
            if((solution.timeSpentPerServer[j] + data.T[j][allJobs[i].id - 1]) <= data.b[solution.servers[j].id - 1]){ // checa se cabe
                newCost = solution.solutionCost - allJobs[i].custo + data.C[j][allJobs[i].id - 1];
                if( newCost < bestCost){
                    choosedJob = allJobs[i];
                    newindexServer = j + 1;
                    newtimeAtServer = data.T[j][allJobs[i].id - 1];
                    costAtServer =  data.C[j][allJobs[i].id - 1];
                    bestCost = newCost;
                    found = true;
                    // std::cout<< solution.solutionCost << " - " << allJobs[i].custo << "+" << + data.C[j][allJobs[i].id - 1] << " = " <<solution.solutionCost - allJobs[i].custo + data.C[j][allJobs[i].id - 1] 
                    // << " " << allJobs[i].id << " " <<  allJobs[i].idServerAlloc << std::endl;
                        
                }
                
            }
        }
    }

    if(found){
        *betterSolutionFound = true;
        if(choosedJob.idServerAlloc == -1){ // job não alocado
            choosedJob.tempo = newtimeAtServer;
            choosedJob.custo = costAtServer;
            choosedJob.idServerAlloc = newindexServer;
            solution.servers[choosedJob.idServerAlloc - 1].jobs.push_back(choosedJob);
            solution.solutionCost = bestCost;
            solution.timeSpentPerServer[choosedJob.idServerAlloc - 1] += choosedJob.tempo;
            solution.nonAllocatedJobs = removeJob(solution.nonAllocatedJobs, choosedJob.id);
        }else{ // caso em que o job estava alocado
            //remover do servidor antigo pelo id do job
            solution.servers[choosedJob.idServerAlloc - 1].jobs = removeJob(solution.servers[choosedJob.idServerAlloc - 1].jobs, choosedJob.id);
            solution.timeSpentPerServer[choosedJob.idServerAlloc - 1] -= choosedJob.tempo; //subtrai o tempo da alocação antiga nesse serve

            //atualizar job com as informações referentes a alocação no novo servidor
            choosedJob.tempo = newtimeAtServer;
            choosedJob.custo = costAtServer;
            choosedJob.idServerAlloc = newindexServer;
            solution.servers[choosedJob.idServerAlloc - 1].jobs.push_back(choosedJob);
            solution.solutionCost = bestCost;
            solution.timeSpentPerServer[choosedJob.idServerAlloc - 1] += choosedJob.tempo;
            solution.nonAllocatedJobs = removeJob(solution.nonAllocatedJobs, choosedJob.id);

        }
    }

    return solution;
}