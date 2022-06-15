#include "../interfaces/Greedy.h"
#include <vector>

using namespace std;

Greedy::Greedy(){
    this->data = NULL;
    this->solution.nonAllocatedJobs = {};
    this->solution.serverAmmount = 0;
    this->solution.servers = {};
    this->solution.solutionCost = -1;
}

/*
Greedy::Greedy(JobXServer data){
    this->data = data;

    // data to work with: servers

    //first step: iterate for each server adding jobs given each server capacity

    std::vector <bool> isJobAssigned;
    isJobAssigned.assign(data.n, false);
    std::vector <int> serverTimeSpent;
    serverTimeSpent.assign(data.m, 0);
    std::vector <Server> servers;
    std::vector <Jobs> jobs;
    int costAux = 0;


    for(unsigned int i = 0; i < data.m; i++){
        for(unsigned int j = 0; j < data.n; j++){
            if(!isJobAssigned[j]){
                if(data.T[i][j] + serverTimeSpent[i] <= data.b[i]){
                    serverTimeSpent[i] += data.T[i][j];
                    isJobAssigned[j] = true;
                    jobs.push_back(Jobs(j + 1, data.T[i][j], data.C[i][j], i+1));
                    costAux += data.C[i][j];
                }
            }
        }
        servers.push_back(Server(i + 1, costAux, jobs, jobs.size()));
        costAux = 0;
        jobs.clear();
    }

    Solution* solution = (Solution*) std::calloc(1, sizeof(Solution));
    solution->servers = servers;
    solution->serverAmmount = data.m;
    solution->solutionCost = 0;
    solution->timeSpentPerServer.assign(data.m, 0);
    for(unsigned int j = 0; j < data.n; j++){
        if(!isJobAssigned[j]){
            solution->nonAllocatedJobs.push_back(Jobs(j+1, 0, data.p, -1));
            solution->solutionCost += data.p;
        }
    }
    for(unsigned int i = 0; i < data.m; i++){
        solution->solutionCost += servers[i].custoParaServidor;
        for(unsigned int j = 0; j < servers[i].jobAmmount; j++){
            solution->timeSpentPerServer[i] += servers[i].jobs[j].tempo;
        }
    }

    this->solution = *solution;
}
*/
Greedy::Greedy(JobXServer data){
    this->data = data;

    std::vector <Jobs> jobList;
    std::vector <Jobs> jobAux;
    std::vector <Server> serverAux;
    std::vector <int> timePerServer;
    
    for(int i = 0; i < data.n; i++){
        jobList.push_back(Jobs(i + 1, 0, data.p, -1));
    }
    int serverTimeSpent, costPerServer, totalCost = 0;
    for(int i = 0; i < data.m; i++){
        serverTimeSpent = 0;
        costPerServer = 0;
        
        for(int j = 0; j < jobList.size(); j++){
            if(data.T[i][jobList[j].id - 1] + serverTimeSpent < data.b[i]){
                serverTimeSpent += data.T[i][j];
                jobAux.push_back(Jobs(jobList[j].id, data.T[i][jobList[j].id - 1], data.C[i][jobList[j].id - 1], i + 1));
                costPerServer += data.C[i][jobList[j].id - 1]; 
                jobList.erase(jobList.begin() + j);
                j--;
            }
        }
        
        totalCost += costPerServer;
        timePerServer.push_back(serverTimeSpent);
        serverAux.push_back(Server(i + 1, costPerServer, jobAux, jobAux.size()));
        jobAux.clear();
    }
    
    Solution* solution = new Solution;
    solution->servers = serverAux;
    solution->solutionCost = totalCost + (jobList.size() * data.p);
    solution->nonAllocatedJobs = jobList;
    solution->timeSpentPerServer = timePerServer;
    this->solution = *solution;
    delete solution;
}