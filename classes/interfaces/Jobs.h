#ifndef JOBS_H
#define JOBS_H

class Jobs{
    public:
        int id, tempo, custo, allocatedServerID;
        Jobs(int id, int tempo, int custo);
};

#endif