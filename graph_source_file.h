#ifndef GRAPH_SOURCE_FILE
#define GRAPH_SOURCE_FILE 
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <cmath>
#include <memory>
#include<vector>
#include "adjacency_list.h"

class FillGraph 
{
 public:
  FillGraph(Graph&, std::stringstream&);
  ~FillGraph();

 private:
  Graph& graph_;
  std::stringstream& buffer_;
};

#endif //GRAPH_SOURCE_FILE
