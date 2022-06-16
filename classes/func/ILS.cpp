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
    Solution* best = new Solution;
    history.push_back(VND.solution);
    int lastIterationWithBetterSolution = 0;
    int currentIteration = 0;
    while(currentIteration - lastIterationWithBetterSolution < THRESHOLD){
        currentIteration++;
        VND = Vnd(ripple(history.back()), data);
        if(VND.solution.solutionCost < best->solutionCost){
            lastIterationWithBetterSolution = currentIteration;
            *best = VND.solution;
        }
        history.push_back(VND.solution);
    }
    this->history = history;
    this->bestFound = *best;
    delete(best);
}