#ifndef GREEDY_H
#define GREEDY_H

#include "JobXServer.h"
#include "Server.h"


struct Solution{
    std::vector <Server> servers;
    std::vector <Jobs> nonAllocatedJobs;
    std::vector  <int> timeSpentPerServer;
    int solutionCost;
    int serverAmmount;
    //bool isValid;
};


class Greedy{
    public:
        Solution solution;
        JobXServer data;
        Greedy(JobXServer instance);
        Greedy();
        void printSolution(Solution*);

};

#endif