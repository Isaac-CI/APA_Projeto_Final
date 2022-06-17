#ifndef GAP_H
#define GAP_H

#include "Greedy.h"

// n5m15A = 240
// n5m15B = 243
// n25m5A = 413
// n30m5A = 377
// n60m10 = 928
// n60m10A = 958

class Gap {
  private: 
    Solution heuristicValue;
    int optimalValue;

  public:
    Gap(Solution heuristicValue, int instanceID);
    void printGap();
    
};

#endif
