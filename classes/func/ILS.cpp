#include"../interfaces/ILS.h"

#define THRESHOLD 10

bool compareSolutionCosts(Solution s1, Solution s2){
    return (s1.solutionCost < s2.solutionCost);
}

Solution ILS::ripple(Solution solution){
    return solution;
}

ILS::ILS(JobXServer data){
    std::vector <Solution> history;
    Greedy guloso = Greedy(data);
    history.push_back(guloso.solution);
    Vnd VND = Vnd(guloso.solution, data);
    history.push_back(VND.solution);
    int iterationsWithoutBetterSolution = 0;
    while(iterationsWithoutBetterSolution < THRESHOLD){
        iterationsWithoutBetterSolution++;
        VND = Vnd(ripple(history.back()), data);
        history.push_back(VND.solution);
    }
    std::sort(history.begin(), history.end(), compareSolutionCosts);
    this->history = history;
    this->bestFound = history.front();
}