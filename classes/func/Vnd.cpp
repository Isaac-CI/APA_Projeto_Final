#include "../interfaces/Vnd.h"

Vnd::Vnd(Solution solution, JobXServer data){
    auto start =  std::chrono::high_resolution_clock::now();
    this->data = data;
    bool keepSolving = true;
    Movements thoseMoves = Movements(solution, data);
    while(keepSolving){
        while(keepSolving){
            thoseMoves.solution = thoseMoves.reInsertionJob(thoseMoves.solution, thoseMoves.data, &keepSolving);
        }
        thoseMoves.solution = thoseMoves.swapServer(thoseMoves.solution, thoseMoves.data, &keepSolving);
    }
    this->solution = thoseMoves.solution;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    this->executionTime = duration;
}