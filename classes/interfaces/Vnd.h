#ifndef VND_H
#define VND_H

#include "movements.h"


class Vnd{
    public:
        JobXServer data;
        Solution solution;

        Vnd(Solution, JobXServer);
};

#endif