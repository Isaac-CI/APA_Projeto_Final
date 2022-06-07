#ifndef VND_H
#define VND_H

#include "Greedy.h"

class Vnd{
    public:
        JobXServer data;
        Solution solution;

        Vnd(Solution, JobXServer);
        Solution swapServer(Solution, JobXServer, bool*);
        Solution changeServer(Greedy);
};

#endif