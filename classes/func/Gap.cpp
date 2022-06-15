#include "../interfaces/Gap.h"
#include "../interfaces/Greedy.h"
#include <vector>

std::vector <int> optimalValues = {1200, 240, 243, 413, 377, 928, 958};

Gap::Gap(Solution heuristicValue, int instanceID){
  try {
    this->heuristicValue = heuristicValue;
    this->optimalValue = optimalValues[instanceID-1];
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

void Gap::printGap(){
  double gap = (((double)this->heuristicValue.solutionCost-this->optimalValue)
    /this->optimalValue)*100;
  
  std::cout  << "Solução encontrada: " << this->heuristicValue.solutionCost << std::endl;
  std::cout  << "Solução ótima: " << this->optimalValue << std::endl;
  std::cout  << "Gap: " << gap << "%" << std::endl;
}