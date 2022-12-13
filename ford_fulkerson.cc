#include "ford_fulkerson.h"
#include <limits>
#include <vector>
#include<algorithm>


FordFulkerson::FordFulkerson()
{
  max_flow_ = 0;
}

//greedy: no residual network
int FordFulkerson::greedy(Graph& graph)
{

  auto current_path = graph.shortest_path();
  while(!current_path.empty())
  { 
    int path_flow = std::numeric_limits<int>::max();   
    for(auto& visited_node : current_path)
    {       
      int capacity = graph.get_capacity(visited_node.first, visited_node.second);
      path_flow = std::min(capacity, path_flow);
    }
    
    max_flow_ += path_flow;

    for(auto& visited_node : current_path)
    { 
      graph.sub_capacity(visited_node.first, visited_node.second, path_flow);
    }    

    current_path = graph.shortest_path();
  }  
  return max_flow_; 
}

//Edmonds - Karp algo: with residual network
int FordFulkerson::residualGraph(Graph& graph)
{
  auto current_path = graph.shortest_path();
  while(!current_path.empty())
  { 
    int path_flow = std::numeric_limits<int>::max();   
    for(auto& visited_node : current_path)
    {       
      int capacity = graph.get_capacity(visited_node.first, visited_node.second);
      path_flow = std::min(capacity, path_flow);
    }
    
    max_flow_ += path_flow;

    for(auto& visited_node : current_path)
    { 
      graph.sub_capacity(visited_node.first, visited_node.second, path_flow);
      graph.add_capacity(visited_node.second, visited_node.first, path_flow);
    }    

    current_path = graph.shortest_path();
  }  
  return max_flow_; 
}
