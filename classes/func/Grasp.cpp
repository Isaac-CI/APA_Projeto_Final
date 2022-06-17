#include"../interfaces/Grasp.h"

Grasp::Grasp(JobXServer data){
    Solution solution = RSG(data);
    this->solution = solution;
}

Solution Grasp::RSG(JobXServer data){
    Solution solution;
    solution.serverAmmount = data.m;
    solution.solutionCost = 0;
    std::vector <Jobs> jobAux;
    std::vector <Jobs> jobInServer[data.m];
    std::vector <int> randomServerID, serverTime, serverCost;
    serverTime.assign(data.m, 0);
    serverCost.assign(data.m, 0);
    int randomServerIndex;

    for(int j = 0; j < data.n; j++){
        jobAux.push_back(Jobs(j + 1, 0, data.p, -1));
    }
    for(int j = 0; j < data.n; j++){
        for(int i = 0; i < data.m; i++){
            randomServerID.push_back(i + 1);
        }
        while(randomServerID.size()){
            randomServerIndex = rand() % randomServerID.size();
            if(serverTime[randomServerID[randomServerIndex] - 1] + data.T[randomServerID[randomServerIndex] - 1][jobAux[j].id - 1] < data.b[randomServerID[randomServerIndex] - 1]){
                jobAux[j].custo = data.C[randomServerID[randomServerIndex] - 1][jobAux[j].id - 1];
                serverCost[randomServerID[randomServerIndex - 1]] += data.C[randomServerID[randomServerIndex] - 1][jobAux[j].id - 1];
                jobAux[j].idServerAlloc = randomServerID[randomServerIndex];
                jobAux[j].tempo = data.T[randomServerID[randomServerIndex] - 1][jobAux[j].id - 1];
                serverTime[randomServerID[randomServerIndex] - 1] += data.T[randomServerID[randomServerIndex] - 1][jobAux[j].id - 1];
                randomServerID.clear();
                break;
            }
            randomServerID.erase(randomServerID.begin() + randomServerIndex);
        }
    }
    for(int j = 0; j < data.n; j++){
        if(jobAux[j].idServerAlloc > 0){
            jobInServer[jobAux[j].idServerAlloc - 1].push_back(jobAux[j]);
        }else{
            solution.nonAllocatedJobs.push_back(jobAux[j]);
            solution.solutionCost += data.p;
        }
    }
    for(int i = 0; i < data.m; i++){
        solution.servers.push_back(Server(i + 1, serverCost[i + 1], jobInServer[i], jobInServer[i].size()));
        solution.servers[i].custoParaServidor = serverCost[i];
        solution.servers[i].jobAmmount = solution.servers[i].jobs.size();
        solution.solutionCost += serverCost[i];
        solution.timeSpentPerServer.push_back(serverTime[i]);
    }
    return solution;
}