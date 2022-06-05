#ifndef GREEDY_H
#define GREEDY_H

#include "JobXServer.h"
#include "Server.h"


typedef struct Solution{
    std::vector <Server> servers;
    std::vector <Jobs> nonAllocatedJobs;
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

};

#endif