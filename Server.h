#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "Jobs.h"

class Server{
    public:
        int id, custoParaServidor = 0;
        std::vector <Jobs> jobs;

        Server(int id, int custoParaServidor, std::vector <Jobs> jobs);
};

#endif
