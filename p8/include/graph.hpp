#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <utility>
#include "solution.hpp"

class graph {

  private:
    int nodes_;
    std::vector<float> d_;
    // std::vector<int> sol_;
    solution sol_;
    float mean_;
  
  public:
    graph(char file[]);
    graph(graph &g);
    graph(){}
    void read(char file[]);
    int pos(int i, int j);
    void set_item(float r, int i, int j);
    void set_d(void);
    void write(void);
    std::pair<int, int> maximum(void);
    std::vector<float> get_graph(void);
    int get_nodes(void);
    float get_item(int i, int j);
    void set_sol(solution s);
    void write_sol(void);
}; 