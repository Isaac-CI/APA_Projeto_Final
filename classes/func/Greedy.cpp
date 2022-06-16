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

// Greedy::Greedy(JobXServer data){
//     this->data = data;

//     std::vector <bool> isJobAssigned;
//     isJobAssigned.assign(data.n, false);
//     std::vector <int> serverTimeSpent;
//     serverTimeSpent.assign(data.m, 0);
//     std::vector <Server> servers;
//     std::vector <Jobs> jobs;
//     int costAux = 0;


//     for(unsigned int i = 0; i < data.m; i++){
//         for(unsigned int j = 0; j < data.n; j++){
//             if(!isJobAssigned[j]){
//                 if(data.T[i][j] + serverTimeSpent[i] <= data.b[i]){
//                     serverTimeSpent[i] += data.T[i][j];
//                     isJobAssigned[j] = true;
//                     jobs.push_back(Jobs(j + 1, data.T[i][j], data.C[i][j], i+1));
//                     costAux += data.C[i][j];
//                 }
//             }
//         }
//         servers.push_back(Server(i + 1, costAux, jobs, jobs.size()));
//         costAux = 0;
//         jobs.clear();
//     }

//     Solution* solution = (Solution*) std::calloc(1, sizeof(Solution));
//     solution->servers = servers;
//     solution->serverAmmount = data.m;
//     solution->solutionCost = 0;
//     solution->timeSpentPerServer.assign(data.m, 0);
//     for(unsigned int j = 0; j < data.n; j++){
//         if(!isJobAssigned[j]){
//             solution->nonAllocatedJobs.push_back(Jobs(j+1, 0, data.p, -1));
//             solution->solutionCost += data.p;
//         }
//     }
//     for(unsigned int i = 0; i < data.m; i++){
//         solution->solutionCost += servers[i].custoParaServidor;
//         for(unsigned int j = 0; j < servers[i].jobAmmount; j++){
//             solution->timeSpentPerServer[i] += servers[i].jobs[j].tempo;
//         }
//     }

//     this->solution = *solution;
// }

Greedy::Greedy(JobXServer data){
    this->data = data;
    int serverTime = 0;
    int serverCost = 0;
    std::vector <Server> serverAux;
    std::vector <Jobs> jobs;
    std::vector <Jobs> jobAux;
    Solution solution;
    solution.solutionCost = 0;
    solution.serverAmmount = data.m;

    for(int j = 0; j < data.n; j++){
        jobs.push_back(Jobs(j + 1, 0, data.p, -1));
    }
    for(int i = 0; i < data.m; i++){
        for(int j = 0; j < jobs.size(); j++){
            if(data.T[i][jobs[j].id - 1] + serverTime < data.b[i]){
                serverTime += data.T[i][jobs[j].id - 1];
                serverCost += data.C[i][jobs[j].id - 1];
                jobs[j].custo = data.C[i][jobs[j].id - 1];
                jobs[j].tempo = data.T[i][jobs[j].id - 1];
                jobs[j].idServerAlloc = i + 1;
                jobAux.push_back(jobs[j]);
                jobs.erase(jobs.begin() + j);
            }
        }
        serverAux.push_back(Server(i + 1, serverCost, jobAux, jobAux.size()));
        solution.timeSpentPerServer.push_back(serverTime);
        solution.solutionCost += serverCost;
        serverCost = 0;
        serverTime = 0;
        jobAux.clear();
    }

    for(int j = 0; j < jobs.size(); j++){
        solution.nonAllocatedJobs.push_back(jobs[j]);
        solution.solutionCost += data.p;
    }
    solution.servers = serverAux;

    this->solution = solution;
}