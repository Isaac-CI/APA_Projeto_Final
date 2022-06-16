#ifndef GREEDY_H
#define GREEDY_H

#include "JobXServer.h"
#include "Server.h"
#include <time.h>
#include <chrono>
#include <cstdlib>
#include <algorithm>


struct Solution{
    std::vector <Server> servers;
    std::vector <Jobs> nonAllocatedJobs;
    std::vector  <int> timeSpentPerServer;
    int solutionCost;
    int serverAmmount;
};


class Greedy{
    public:
        Solution solution;
        JobXServer data;
        Greedy(JobXServer instance);
        Greedy();

};

#endif