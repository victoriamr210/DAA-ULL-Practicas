#include <iostream>
#include "strategy.hpp"
#include "graph.hpp"
#include "solution.hpp"
#include <cmath>
#include <time.h>

class VNS : public algoritmo{
  graph grafo;

  void set_graph(graph &g){
    grafo = g;
    // grafo.write();
  }

  void solve(graph &g){
    srand(time(NULL));
    set_graph(g);
    solution a = execute();
    a.write();
  }

  solution execute(void){
    
  }
};