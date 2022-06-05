#ifndef JOBXSERVER_H
#define JOBXSERVER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


class JobXServer {
    public:
        int n, m, p;
        std::vector <std::vector <int>> T, C;
        std::vector<int> b;
        
        JobXServer(const char*);
        JobXServer();
        void printProblemInput();

};

#endif