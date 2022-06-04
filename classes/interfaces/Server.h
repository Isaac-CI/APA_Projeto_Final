#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include "Jobs.h"

class Server{
    public:
        int id, custoParaServidor = 0, jobAmmount;
        std::vector <Jobs> jobs;

        Server(int id, int custoParaServidor, std::vector <Jobs> jobs, int jobAmmount);
};

#endif
