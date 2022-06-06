#ifndef VND_H
#define VND_H

#include "Greedy.h"

class Vnd{
    public:
        Greedy guloso;
        Vnd(Greedy*);
        Solution* swapServer(Solution*, JobXServer*);
        Solution* changeServer(Solution*, JobXServer*);
};

#endif