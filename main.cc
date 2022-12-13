#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <cmath>
#include <memory>
#include<vector>
#include <chrono>
#include "adjacency_list.h"
#include "graph_source_file.h"
#include "ford_fulkerson.h"

int main(int argc, char *argv[])
{ 
 try
 {
   if(argc == 1)
   {
     //--------------------------------------
     int nodes_number = 5; 
     Graph graph(nodes_number, 1, 4);
     graph.add_forward_backward_edg(1, 3, 2);
     graph.add_forward_backward_edg(1, 2, 3);
     graph.add_forward_backward_edg(2, 3, 5);
     graph.add_forward_backward_edg(2, 4, 2);
     graph.add_forward_backward_edg(3, 4, 3);
     //--------------------------------------
     //int nodes_number = 7; 
     //Graph graph(nodes_number, 1, 6);
     //graph.add_forward_backward_edg(1, 3, 12);
     //graph.add_forward_backward_edg(1, 2, 12);
     //graph.add_forward_backward_edg(2, 3, 4);
     //graph.add_forward_backward_edg(2, 4, 6);
     //graph.add_forward_backward_edg(2, 5, 10);
     //graph.add_forward_backward_edg(3, 5, 11);
     //graph.add_forward_backward_edg(5, 4, 8); 
     //graph.add_forward_backward_edg(4, 6, 12);
     //graph.add_forward_backward_edg(5, 6, 12);
     //--------------------------------------
     std::cout << graph << std::endl;
     std::cout << graph.get_edges() << std::endl;
     FordFulkerson ffu; 
     //std::cout << ffu.greedy(graph) << std::endl;
     std::cout << ffu.residualGraph(graph) << std::endl;
   } 
   else if(argc >= 2)
   {
       //std::cerr << "Input file missing." << std::endl;
       //return 1;
     

     std::regex find_space("[\\s]");
     
     std::ifstream rfile;
     rfile.open(argv[1]);
     std::stringstream buffer;
     buffer << rfile.rdbuf();

     ///////////////////////////////
     //Set Graph nodes from file.
     std::string l_nodes;
     std::getline(buffer, l_nodes, '\n');
     std::vector<std::string> nodesValues;
     std::regex_token_iterator<std::string::iterator> rend;
     std::regex_token_iterator<std::string::iterator> str_nodes(l_nodes.begin(), l_nodes.end(), find_space, -1);
     while(str_nodes != rend)
     { 
      nodesValues.push_back(*str_nodes);
      str_nodes++;
     }
     int total_nodes = ((std::stoi(nodesValues[2])) + 1);
     ////////////////////////////////  
     
     Graph gr(total_nodes, 0, 0);
     FillGraph fg(gr, buffer);


     std::cout << gr << std::endl;
     std::cout << gr.get_edges() << std::endl;

     //std::cout << gr << std::endl;
     //
     FordFulkerson ff;  
     auto start_ff = std::chrono::high_resolution_clock::now();
     //std::cout << std::endl;
     //std::cout << "The maximum flow on a weighted directed graph is : "<< ff.greedy(gr) << std::endl;
     std::cout << "The maximum flow on a weighted directed graph is : "<< ff.residualGraph(gr) << std::endl;
     auto stop_ff = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_ff - start_ff);
     std::cout << "Ford - Fulkerson algorithm takes " << duration.count() << " microseconds for solving maximum flow problem" << std::endl;
     //
     std::cout << std::endl;
   }
 }
 catch(std::exception &e)
 {
   std::cerr << "Exception: " << e.what() << std::endl;
 } 

 return 0;
}
