#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include "Greedy.h"


class Movements{
    public:
        JobXServer data;
        Solution solution;

        Movements(Solution, JobXServer);
        Solution swapServer(Solution, JobXServer, bool*);
        Solution reInsertionJob(Solution, JobXServer, bool*);
};

#endif