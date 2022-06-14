#ifndef JOBS_H
#define JOBS_H

class Jobs{
    public:
        int id, tempo, custo, idServerAlloc;
        Jobs(int id, int tempo, int custo, int idServerAlloc);
        Jobs();
};

#endif