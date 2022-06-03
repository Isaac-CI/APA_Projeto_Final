#ifndef GREEDY_
#define GREEDY_



#include "JobXServer.h"
#include "Server.h"


class Greedy{
    public:
        int custoTotal;
        std::vector <Server> servers;

        Greedy(JobXServer instance);

};

#endif