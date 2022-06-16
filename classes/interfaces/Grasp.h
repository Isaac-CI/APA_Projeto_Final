#ifndef GRASP_H
#define GRASP_H

#include "../interfaces/Vnd.h"

class Grasp{
    public:
        Solution solution;
        Grasp(JobXServer);
        Solution RSG(JobXServer);
};

#endif