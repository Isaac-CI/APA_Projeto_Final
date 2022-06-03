#include <iostream>
#include <vector>
#include "JobXServer.h"
#include "Server.h"
#include "Jobs.h"


//using namespace std;

int main(void){

    JobXServer instance = JobXServer("./input.txt");
    
    int m = instance.m, n = instance.n;
    std::vector <std::vector <int>> T = instance.T;
    
    std::vector <Server> servers;
    for(int i  = 0; i < m; i++){
        std::vector <Jobs> jobs;
        for(int j = 0; j < n; j++) {
            jobs.push_back(Jobs(j+1,T[i][j]));
        }

        servers.push_back(Server(i+1,0,jobs));
    }

    instance.printProblemInput();
    
    std::cout << "\n";
    
    for(int i = 0;i < m; i++){
        for(int j = 0; j < n; j++){
            std::cout << servers[i].jobs[j].id << " "<<servers[i].jobs[j].tempo << std::endl;
        }
        std::cout << "\n";
        
    }
   
    return 0;
}
