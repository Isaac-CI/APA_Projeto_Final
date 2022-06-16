#ifndef VND_H
#define VND_H

#include "movements.h"


class Vnd{
    public:
        std::chrono::microseconds executionTime;
        JobXServer data;
        Solution solution;

        Vnd(Solution, JobXServer);
};

#endif