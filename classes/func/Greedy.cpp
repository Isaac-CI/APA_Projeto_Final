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
Greedy::Greedy(JobXServer instance){
    this->data = instance;
    int m = instance.m, n = instance.n;
    std::vector <std::vector <int>> T = instance.T; //time
    std::vector <std::vector <int>> C = instance.C; // costs
    std::vector<int> b = instance.b; // server capabilities

    // data to work with: servers

    //first step: iterate for each server adding jobs given each server capacity

    std::vector <bool> isJobAssigned;
    isJobAssigned.assign(n, false);
    std::vector <int> serverTimeSpent;
    serverTimeSpent.assign(m, 0);
    std::vector <Server> servers;
    std::vector <Jobs> jobs;
    int costAux = 0;


    for(unsigned int i = 0; i < m; i++){
        for(unsigned int j = 0; j < n; j++){
            if(!isJobAssigned[j]){
                if(T[i][j] + serverTimeSpent[i] <= b[i]){
                    serverTimeSpent[i] += T[i][j];
                    isJobAssigned[j] = true;
                    jobs.push_back(Jobs(j + 1, T[i][j], C[i][j], i+1));
                    costAux += C[i][j];
                }
            }
        }
        servers.push_back(Server(i + 1, costAux, jobs, jobs.size()));
        costAux = 0;
        jobs.clear();
    }

    Solution* solution = (Solution*) std::calloc(1, sizeof(Solution));
    solution->servers = servers;
    solution->serverAmmount = m;
    solution->solutionCost = 0;
    solution->timeSpentPerServer.assign(m, 0);
    for(unsigned int j = 0; j < n; j++){
        if(!isJobAssigned[j]){
            solution->nonAllocatedJobs.push_back(Jobs(j+1, 0, instance.p, -1));
            solution->solutionCost += instance.p;
        }
    }
    for(unsigned int i = 0; i < m; i++){
        solution->solutionCost += servers[i].custoParaServidor;
        for(unsigned int j = 0; j < servers[i].jobAmmount; j++){
            solution->timeSpentPerServer[i] += servers[i].jobs[j].tempo;
        }
    }

    //printSolution(solution);
    //std::cout << "Custo após guloso: " << solution->solutionCost << std::endl;
    this->solution = *solution;


    // for(int i = 0; i < servers.size(); i++){
    //     std::cout << solution->servers[i].id << std::endl;
    // }

    // prints the values for the sake of debugging
    // for(int i = 0;i < m; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cout << servers[i].jobs[j].id << " "<<servers[i].jobs[j].tempo << std::endl;
    //     }
    //     std::cout << "\n";
    // }

}