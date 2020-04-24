#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <limits>

class GRASP : public algoritmo{
  std::vector<solution> solutions_;
  int RCL_size = 3;
  const int N = 1000;

  // std::vector<int> RCL;
  graph grafo;
  
  void set_graph(graph g){
    grafo = g;
  }

  void solve(graph &g){
    execute(g);
  }

  solution execute(graph &g){
    set_graph(g);
    preprocess();
    // set_graph(preprocess(g));
    // graph processed = preprocess(g);
    int cont = 0;
    // while (cont != N) {
    std::cout << "execute\n";
      std::vector<int> v =construction();
      for(int i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
      }
      std::cout << "\n";
    // }

  }

  void preprocess(void){
    // graph aux = g;
    for(int i = 0; i < grafo.get_nodes(); i++){
      for(int j = 0; j < grafo.get_nodes(); j++){
        if (grafo.get_item(i,j) < 0){
          grafo.set_item(0,i,j);
        }
      }
    }
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

  std::vector<int> buildRCL(std::vector<float> dis){
    std::vector<int> rcl(RCL_size);
    std::vector<float> aux = dis;
    int index = 0;
    for(int i = 0; i < RCL_size; i++){
      float max = std::numeric_limits<float>::min();
      for(int j = 0; j < grafo.get_nodes(); j++){
        if(aux[j] > max){
          max = aux[j];
          index = j;
        }
      }
      rcl[i]=index;
      aux[index] = std::numeric_limits<float>::min();
    }
    return rcl;
  }

  std::vector<int> construction(void){
    srand(time(NULL));
    int i = rand() % grafo.get_nodes();
    int indexJ = rand() % grafo.get_nodes();
    int n = rand() % grafo.get_nodes();
    std::vector<int> s(grafo.get_nodes());
    s[i] = 1; // nodo por el que se empieza
    int k = 1;
    while(k < n){
      std::vector<int> candidates = get_candidates(s);
      std::vector<float> dispersion = get_afinity(s, candidates);
      std::vector<int> rcl = buildRCL(dispersion);
    }

  }

  float getMd(std::vector<int> s, int index){
    float dispersion;
    int num;
    for(int i = 0; i < s.size(); i++){
      if(s[i] == 1){
        num++;
        for(int j = 0; j < s.size(); j++){
          if(s[j] == 1 && i!= j){
            dispersion = grafo.get_item(i,j);
          }
        }
      }
    }
    return (dispersion / num);
  }
  std::vector<int> get_rcl(void){

  }
};