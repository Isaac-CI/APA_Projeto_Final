#include "../interfaces/Vnd.h"

Vnd::Vnd(Solution solution, JobXServer data){
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
}