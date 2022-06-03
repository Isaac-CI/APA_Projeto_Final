#ifndef JOBXSERVER_
#define JOBXSERVER_

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


class JobXServer {
    public:
        int n, m;
        std::vector <std::vector <int>> T, C;
        std::vector<int> b;
        
        JobXServer(const char*);
        void printProblemInput();

};

#endif