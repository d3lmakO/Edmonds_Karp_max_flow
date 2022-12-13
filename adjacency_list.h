#ifndef ADJACENCY_LIST
#define ADJACENCY_LIST
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include <unordered_map>
#include <boost/container/flat_map.hpp>


class Graph
{
 public:
  Graph(int nodes,int source,int sink);
  ~Graph();
  //void add_forward_edg(int u,int v,int c);
  void add_forward_backward_edg(int u,int v,int c);
  void set_capacity(int, int, int); 
  void sub_capacity(int, int, int);
  void add_capacity(int, int, int);
  const int& get_capacity(int, int);
  const int& get_nodes() const;
  void set_nodes(int);
  int get_edges();
  const int& get_source() const;
  const int& get_sink() const;
  void set_source(int s);
  void set_sink(int s);
  const boost::container::flat_map<int, int>& node_edges(int);
  void printGraph(std::ostream&) const;
  friend std::ostream& operator<<(std::ostream&, const Graph&);

  //shortest path for Ford - Fulkerson -> greedy and Edmonds - Karp algorithm
  std::vector<std::pair<int, int>> shortest_path();
 private:
  int nodes_;
  int source_;
  int sink_;
  std::vector<boost::container::flat_map<int, int>> adjList_;
};
 
#endif //ADJACENCY_LIST

