#ifndef FORD_FULKERSON
#define FORD_FULKERSON
#include "adjacency_list.h"
#include <memory>
#include <map>
class FordFulkerson
{
 public:
  FordFulkerson();
  ~FordFulkerson(); 
  int greedy(Graph&);
  int residualGraph(Graph&);
 private:
  int max_flow_;
};

#endif //FORD_FULKERSON
