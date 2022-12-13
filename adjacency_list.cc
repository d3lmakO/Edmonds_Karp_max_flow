#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include "adjacency_list.h"

Graph::Graph(int nodes, int source, int sink)
{
  nodes_ = nodes; 
  source_ = source; 
  sink_ = sink;
  adjList_.reserve(nodes_);
  boost::container::flat_map<int, int> edges;
  for(int i = 0; i < nodes_; ++i)
  {
    adjList_.emplace_back(edges); 
  }
}


void Graph::set_capacity(int u,int v,int c)
{
  adjList_[u][v] = c;
}

void Graph::sub_capacity(int u, int v, int c)
{ 
  adjList_[u][v] -= c;
}

void Graph::add_capacity(int u, int v, int c)
{ 
  adjList_[u][v] += c;
}

const int& Graph::get_capacity(int u, int v)
{ 
  return adjList_[u][v];
}

const int& Graph::get_nodes() const
{
  return nodes_; 
}

void Graph::set_nodes(int nodes)
{
  nodes_ = nodes; 
}

int Graph::get_edges()
{
  int count = 0;
  for(int n = 0; n < nodes_; ++n)
  {
    for(const auto& el : adjList_[n])
    {
      count += 1;
    }
  }
  
  return count;
}

const int& Graph::get_source() const
{
  return source_; 
}

const int& Graph::get_sink() const
{
  return sink_; 
}

void Graph::set_source(int s)
{
  source_ = s; 
}

void Graph::set_sink(int s)
{
  sink_ = s; 
}

void Graph::add_forward_backward_edg(int u,int v,int c)
{
  if(u < 0 || u >= nodes_ ||
     v < 0 || v >= nodes_ ) { return; } 
  //Add edge:
  //start node -> u
  //end node -> v
  //capacity -> c

  //forward
  adjList_[u].emplace(std::make_pair(v, c));
  //backward
  adjList_[v].emplace(std::make_pair(u, 0));
}

const boost::container::flat_map<int, int>& Graph::node_edges(int node)
{
  return adjList_.at(node); 
}


/*Print the adjacency list.*/
void Graph::printGraph(std::ostream& out = std::cout) const
{
  out << "\n Graph adjacency list.";
  out << "\n Source: " << source_;
  out << "\n Sink: " << sink_;
  out << "\n start node --> (end node, capacity)";
  for(int n = 1; n < nodes_; ++n)
  {
    out << " \n [" << n << "] -->";
    for(const auto&  n_a : adjList_[n])
    { 
      out << "(" << n_a.first  << ", " 
                 << n_a.second << ") ";
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Graph &grp)
{
 grp.printGraph(os);
 return os;
}

std::vector<std::pair<int, int>> Graph::shortest_path()
{
   std::vector<std::pair<int, int>> bfsPath; 
   std::vector<std::pair<int, int>> shortest_path;
   std::queue<int> q_nodes;
   std::map<int, bool> nodes_visited;

   q_nodes.push(source_);
   nodes_visited[source_] = true;
   
   //find shortest path from source to sink
   while(!q_nodes.empty() && !nodes_visited[sink_])
   {
     int node = q_nodes.front();
     q_nodes.pop();

     for(const auto& neighbor : adjList_.at(node))
     {
       //node visited is false and capacity between nodes is greater than zero.
       if(((!nodes_visited[neighbor.first]) && (neighbor.second > 0)))
       {
         q_nodes.push(neighbor.first);
         nodes_visited[neighbor.first] = true;
         bfsPath.emplace_back(std::make_pair(node, neighbor.first));
         //std::cout << node << "  " << neighbor.first << std::endl;
       }  
     } 
   }

   if(!nodes_visited[sink_])
   {
     return shortest_path;
   }
   int current_node = sink_;
   auto path_node = bfsPath.rbegin();
   while(current_node != source_) 
   {
     if(path_node->second == current_node)
     { 
       shortest_path.emplace_back(*path_node);
       current_node = path_node->first;
       ++path_node;
     }
     else
     {
       ++path_node;
     }
   }

   return shortest_path;
}

//std::vector<int> Graph::bfs_level()
//{ 
//  std::vector<int> node_level;
//  std::queue<int> q_nodes;
//  for(int n = 0; n < nodes_; ++n)
//  {
//    //level undefined for every node
//    node_level[n] = -1; 
//  }
// 
//  node_level[source_] = 0;
//  q_nodes.push(source_);
//
//  while(!q_nodes.empty())
//  {
//    int node = q_nodes.front();
//    q_nodes.pop();
//    for(const auto& neighbor : adjList_.at(node))
//    {
//      if((node_level[neighbor.first] < 0) && neighbor.second > 0)
//      {
//        node_level[neighbor.first] = node_level[node] + 1;
//        q_nodes.push(neighbor.first);
//      }
//    }
//  }
//
//  //return node_level[sink] < 0 ? false : true;
//  return node_level;
//}

