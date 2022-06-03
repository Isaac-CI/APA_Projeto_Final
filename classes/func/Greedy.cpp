#include "../interfaces/Greedy.h"
#include <vector>
#include <algorithm>


bool comparator(const Jobs& lhs, const Jobs& rhs) {
   return lhs.tempo < rhs.tempo;
}

Greedy::Greedy(JobXServer instance){
    int m = instance.m, n = instance.n;
    std::vector <std::vector <int>> T = instance.T; //time
    std::vector <std::vector <int>> C = instance.C; // costs
    std::vector<int> b = instance.b; // server capabilities

    std::vector <Server> servers;
    // create a vector of servers and vectors of jobs for each server
    for(int i  = 0; i < m; i++){
        std::vector <Jobs> jobs;
        for(int j = 0; j < n; j++) {
            jobs.push_back(Jobs(j+1,T[i][j], C[i][j]));
        }
        servers.push_back(Server(i+1,0,jobs)); // initial cost of each server is 0 
    }

    // data to work with: servers

    // first step: Sorting the vectors

    for(int i = 0;i < m; i++){
        sort(servers[i].jobs.begin(), servers[i].jobs.end(), &comparator);
    }


    //second step: iterate for each server adding jobs given each server capacity
    
    // prints the values for the sake of debugging
    // for(int i = 0;i < m; i++){
    //     for(int j = 0; j < n; j++){
    //         std::cout << servers[i].jobs[j].id << " "<<servers[i].jobs[j].tempo << std::endl;
    //     }
    //     std::cout << "\n";
    // }

}

