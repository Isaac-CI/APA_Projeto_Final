#ifndef GREEDY_
#define GREEDY_



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
        int custoTotal;
        std::vector <Server> servers;

        Greedy(JobXServer instance, Solution* solution);

};

#endif