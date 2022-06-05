#include "../interfaces/Greedy.h"
#include <vector>
#include <algorithm>

using namespace std;



void printSolution(Solution* s){
    std::cout << "quantidade de servers: " <<s->serverAmmount << std::endl;
    for(unsigned int i = 0; i < s->serverAmmount; i++){
        for(unsigned int j = 0; j < s->servers[i].jobAmmount; j++){
            if(s->servers[i].id == s->servers[i].jobs[j].allocatedServerID){
                std::cout << "O Job " << s->servers[i].jobs[j].id << " foi alocado ao Server " 
                        << s->servers[i].id << " custando " << s->servers[i].jobs[j].custo << " e demorando " 
                                    << s->servers[i].jobs[j].tempo << " para ser executado." << std::endl;
            }
        }
    }
    for(unsigned int i = 0; i < sizeof(s->nonAllocatedJobs) / sizeof(Jobs); i++){
        std::cout << "O Job " << s->nonAllocatedJobs[i].id 
        << " não foi alocado em nenhum dos servidores externos, por isso, foi alocado no servidor local, com um custo de: "
        << s->nonAllocatedJobs[i].custo << std::endl;
    }
}

bool comparator(const Jobs& lhs, const Jobs& rhs) {
   return lhs.tempo < rhs.tempo;
}

Server sortJobsInServer(Server s){
    std::sort(s.jobs.begin(), s.jobs.end(), &comparator);
    return s;
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

    std::vector <Server> servers;
    // create a vector of servers and vectors of jobs for each server
    for(int i  = 0; i < m; i++){
        std::vector <Jobs> jobs;
        for(int j = 0; j < n; j++) {
            jobs.push_back(Jobs(j+1,T[i][j], C[i][j]));
        }
        servers.push_back(Server(i+1,0,jobs, n)); // initial cost of each server is 0
    }

    // data to work with: servers

    // first step: Sorting the vectors

    for(int i = 0; i < m; i++){
        sortJobsInServer(servers[i]);
    }

    //second step: iterate for each server adding jobs given each server capacity

    std::vector <bool> isJobAssigned;
    isJobAssigned.assign(n, false);
    std::vector <int> serverTimeSpent;
    serverTimeSpent.assign(m, 0);
    bool flag;

    for(unsigned int i = 0; i < m; i++){
        for(unsigned int j = 0; j < n; j++){
            if(!isJobAssigned[j]){
                if(servers[i].jobs[j].tempo + serverTimeSpent[i] <= b[i]){
                    serverTimeSpent[i] += servers[i].jobs[j].tempo;
                    isJobAssigned[j] = true;
                    servers[i].jobs[j].allocatedServerID = servers[i].id;
                    servers[i].jobs[j].custo = C[i][j];
                    servers[i].jobs[j].tempo = T[i][j];
                    servers[i].custoParaServidor += servers[i].jobs[j].custo;
                }
            }
        }
    }
    Solution* solution = (Solution*) std::calloc(1, sizeof(Solution));
    solution->servers = servers;
    solution->serverAmmount = m;
    solution->solutionCost = 0;
    for(unsigned int j = 0; j < n; j++){
        if(!isJobAssigned[j]){
            solution->nonAllocatedJobs.push_back(Jobs(j+1, 0, instance.p));
            solution->solutionCost += instance.p;
        }
    }

    for(unsigned int i; i < n; i++){
        solution->solutionCost += servers[i].custoParaServidor;
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

