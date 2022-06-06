#include "../interfaces/Greedy.h"
#include <vector>
#include <algorithm>

using namespace std;



void printSolution(Solution* s){
    std::cout << "quantidade de servers: " <<s->serverAmmount << std::endl;
    for(unsigned int i = 0; i < s->serverAmmount; i++){
        for(unsigned int j = 0; j < s->servers[i].jobAmmount; j++){
            std::cout << "O Job " << s->servers[i].jobs[j].id << " foi alocado ao Server " 
                << s->servers[i].id << " custando " << s->servers[i].jobs[j].custo << " e demorando " 
                    << s->servers[i].jobs[j].tempo << " para ser executado." << std::endl;
        }
        std::cout << "O tempo gasto para processar todos os jobs alocados no server " << s->servers[i].id << " foi de: " 
                    << s->timeSpentPerServer[i] << " unidades." << std::endl;
    }
    for(unsigned int i = 0; i < s->nonAllocatedJobs.size(); i++){
        std::cout << "O Job " << s->nonAllocatedJobs[i].id 
        << " não foi alocado em nenhum dos servidores externos, por isso, foi alocado no servidor local, com um custo de: "
        << s->nonAllocatedJobs[i].custo << std::endl;
    }
}


Greedy::Greedy(){
    this->data = NULL;
    this->solution.nonAllocatedJobs = {};
    this->solution.serverAmmount = 0;
    this->solution.servers = {};
    this->solution.solutionCost = -1;
}

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
                    jobs.push_back(Jobs(j + 1, T[i][j], C[i][j]));
                    costAux += C[i][j];
                }
            }
        }
        servers.push_back(Server(i + 1, costAux, jobs, jobs.size()));
        costAux = 0;
        jobs.clear();
        std::cout << "Quantidade de jobs no servidor " << i+1 << ": " << servers[i].jobs.size() << std::endl;
    }

    Solution* solution = (Solution*) std::calloc(1, sizeof(Solution));
    solution->servers = servers;
    solution->serverAmmount = m;
    solution->solutionCost = 0;
    solution->timeSpentPerServer.assign(m, 0);
    for(unsigned int j = 0; j < n; j++){
        if(!isJobAssigned[j]){
            solution->nonAllocatedJobs.push_back(Jobs(j+1, 0, instance.p));
            solution->solutionCost += instance.p;
        }
    }
    for(unsigned int i = 0; i < m; i++){
        solution->solutionCost += servers[i].custoParaServidor;
        for(unsigned int j = 0; j < servers[i].jobAmmount; j++){
            solution->timeSpentPerServer[i] += servers[i].jobs[j].tempo;
        }
    }

    printSolution(solution);
    this->solution = *solution;

    // prints the values for the sake of debugging
    // for(int i = 0;i < m; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cout << servers[i].jobs[j].id << " "<<servers[i].jobs[j].tempo << std::endl;
    //     }
    //     std::cout << "\n";
    // }

}

