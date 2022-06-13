#ifndef ILS_H
#define ILS_H

#include "../interfaces/Vnd.h"

class ILS{
    public:
        std::vector <Solution> history;
        Solution bestFound;
        ILS(JobXServer);
        Solution ripple(Solution);
};

#endif