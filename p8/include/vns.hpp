#include <iostream>
#include "strategy.hpp"
#include "graph.hpp"
#include "solution.hpp"
#include <cmath>
#include <time.h>

class VNS : public algoritmo{
  graph grafo;
  const int ITERATIONS = 1000;
  const int IMPROVEMENT = 50;
  const int KMAX = 3;

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
    std::vector<int> cand = get_candidates();
    int size = (rand() % (grafo.get_nodes() -2)) + 2;
    std::vector<int> sol = constructor(cand, size);
    std::cout <<"sol: "; write(sol);
    sol = local_search(sol);
    std::vector<int> s;
    std::cout <<"sol: "; write(sol);
    float mean = getMd(sol);
    int cont = 0;
    int noChange = 0;
    int k = 1;
    while(cont < ITERATIONS && noChange < IMPROVEMENT){
      k = 1;
      while(k <= KMAX){
        s = shake(cand, size, k);
        std::vector<int> localBest = local_search(s);
        // std::cout << "local: "; write(localBest);
        float aux_mean = getMd(s);
        // std::cout << "aux: " << aux_mean << " mean: " << mean << "\n";
        if(aux_mean > mean){
          s = localBest;
          mean = aux_mean;
          k = 1;
          noChange = 0;
        } else {
          k++;
          noChange++;
        }
      }
    }
    return solution(s, mean);
  }

   std::vector<int> constructor(std::vector<int> cand, int size){
   
    std::vector<int> sol;
    // std::vector<int> cand = get_candidates(sol);
    // int size = (rand() % (grafo.get_nodes() - 2)) + 2;
    // std::cout << "cand: "; write(cand);
    while(sol.size() < size){
      int element = rand() % cand.size();
      if(std::find(sol.begin(), sol.end(), cand[element]) == sol.end()) {
        sol.push_back(element);
      }
      // std::cout << "sol: "; write(sol);
    }
    return sol;
  }

  std::vector<int> local_search(std::vector<int> sol){
    bool flag = true;
    while(flag){
      flag = false;
      int k = find_k(sol);
      std::vector<int> aux;
      if(k != -1){
        flag=true;
        sol.erase(sol.begin() + k);
      } 
    }
    return sol;
  }

  std::vector<int> shake(std::vector<int> cand, int sol_size, int k){
    int size = (rand() % 2 == 1) ? sol_size + k : sol_size - k;
    if(size < sol_size + k){
      size = sol_size + k;
    }
    if(size > cand.size()){
      size = cand.size();
    }
    return constructor(cand, size);
  }


  int find_k(std::vector<int> sol) {
    std::vector<int> aux;
    aux.push_back(-1);
    float current = getMd(sol);
    for(int i = 0; i < sol.size(); i++) {
      const int vertex = sol[i];
      sol.erase(sol.begin() + i);
      float test = getMd(sol); 
      sol.insert(sol.begin() + i, vertex);
      if(test > current) {
        current = test;
        aux.clear();
        aux.push_back(i);
      } else if(test == current) {
        aux.push_back(i);
      }
    }
    //std::cout << aux.size() << std::endl;
    int index = rand() %  (aux.size());
    //std::cout << index << std::endl;
    return aux[index]; 
  }

   /* Funcion que calcula la media de dispersión de un conjunto de nodos*/
  float getMd(std::vector<int> s) {
    float sum;

    if(s.size() == 0){
      return -INFINITY;
    }
    for(int i = 0; i < s.size(); i++){
      for(int j = i + 1; j < s.size(); j++){
        sum += grafo.get_item(s[i],s[j]);

      }
    // std::cout << "\n";
    }
    // if()
    return sum / s.size();
  }

   std::vector<int> get_candidates(void){
    std::vector<int> cand;
    for(int i = 0; i < grafo.get_nodes(); i++){
      cand.push_back(i);
    }
    return cand;
  }

    /*Funcion que escribe un vector*/
  void write(std::vector<int> s){
    for(int i = 0; i < s.size(); i++){
      std::cout << s[i] << " ";
    }
    std::cout << "\n";
  }
};