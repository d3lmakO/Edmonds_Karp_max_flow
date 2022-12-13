#include <algorithm>
#include "graph_source_file.h"

FillGraph::FillGraph(Graph& grp, std::stringstream& buf) : graph_(grp), buffer_(buf)
{
  std::regex find_space("[\\s]");
  //number of nodes for graph declaration
  //std::regex find_n_nodes("p[\\s][\\w][\\s][0-9]+");
  //edges
  std::regex find_edge("a[\\s][0-9]+");
  //source for min max problem
  std::regex find_source("n[\\s][0-9][\\s]s");
  //sink for min max problem
  std::regex find_sink("n[\\s][0-9][\\s]t");
  std::regex_token_iterator<std::string::iterator> rend;

  std::string line;
  int memory_space = graph_.get_nodes();
  std::vector<std::string> strValues;
  std::vector<std::vector<int>> memory_edge(memory_space);
  bool edge_in = false;
  
  while(std::getline(buffer_, line, '\n'))
  { 
    std::regex_token_iterator<std::string::iterator> str_it(line.begin(), line.end(), find_space, -1);

    if((std::regex_search(line, find_edge)))
    { 
      while(str_it != rend)
      { 
       strValues.emplace_back(*str_it);
       ++str_it;
      }
      /////////////////////////////////////////////////////////////////
      //loop control: prevents insertion of edges in opposite direction
      if(!memory_edge[std::stoi(strValues[1])].empty())
      {
        for(auto edge = memory_edge[std::stoi(strValues[1])].begin();
                 edge != memory_edge[std::stoi(strValues[1])].end();)
        {
          if((*edge) ==  std::stoi(strValues[2]))
          {
            edge_in = true;
            edge = memory_edge[std::stoi(strValues[1])].end();
          }
          else 
          {
            ++edge;
          }
        }
      }
      //////////////////////////////////////////////////////////////////
      if((std::stoi(strValues[3]) > 0) && (edge_in == false))
      {
        graph_.add_forward_backward_edg(std::stoi(strValues[1]),
                                        std::stoi(strValues[2]),
                                        std::stoi(strValues[3]));        
        memory_edge[std::stoi(strValues[2])].emplace_back(std::stoi(strValues[1])); 
      }
      edge_in = false;
    }
    else if((std::regex_search(line, find_source)))
    {
      while(str_it != rend)
      { 
       strValues.emplace_back(*str_it);
       str_it++;
      }
      graph_.set_source(std::stoi(strValues[1]));
    } 
    else if((std::regex_search(line, find_sink)))
    {  
      while(str_it != rend)
      { 
       strValues.emplace_back(*str_it);
       str_it++;
      }
      graph_.set_sink(std::stoi(strValues[1]));
    } 
    else 
    {
      std::cout << std::endl; 
    }
    strValues.clear();
  } 
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

}


