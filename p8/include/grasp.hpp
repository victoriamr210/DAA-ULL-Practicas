#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <limits>

class GRASP {
  std::vector<solution> solutions_;
  int RCL_size = 3;
  const int N = 1000;

  // std::vector<int> RCL;
  graph grafo;
  
  void set_graph(graph &g){
    grafo = g;
  }

  void solve(graph &g){
    solution execute(graph &g);
  }

  solution execute(graph &g){
    set_graph(preprocess(g));
    graph processed = preprocess(g);
    int cont = 0;
    while (cont != N) {
      construction(processed);
    }

  }

  graph preprocess(graph &g){
    graph aux = g;
    for(int i = 0; i < aux.get_nodes(); i++){
      for(int j = 0; j < aux.get_nodes(); j++){
        if (aux.get_item(i,j) < 0){
          aux.set_item(0,i,j);
        }
      }
    }
    return g;
  }
  
  std::vector<int> get_candidates(std::vector<int> s) {
    std::vector<int> cand(s.size());
    for(int i = 0; i < cand.size(); i++){
      if(s[i] == 0) {
        cand[i] = 1;
      } else{
        cand[i] = 0;
      }
    }
    return cand;
  }

  std::vector<float> get_afinity(std::vector<int> s, std::vector<int> cand){
    std::vector<float> aux(s.size());
    for(int i = 0; i < s.size(); i++){
      if(cand[i] == 1){
        aux[i] = getMd(s,i);
      } else {
        aux[i] = std::numeric_limits<float>::min();
      }
    }
    return aux;
  }

  std::vector<int> construction(graph &g){
    srand(time(NULL));
    int i = rand() % g.get_nodes();
    int indexJ = rand() % g.get_nodes();
    int n = rand() % g.get_nodes();
    std::vector<int> s(g.get_nodes());
    s[i] = 1; // nodo por el que se empieza
    int k = 1;
    while(k < n){
      std::vector<int> candidates = get_candidates(s);
      std::vector<float> dispersion = get_afinity(s, candidates);
    }

  }

  float getMd(std::vector<int>, int index){
    
  }
  std::vector<int> get_rcl(void){

  }
};