#include <iostream>
#include "strategy.hpp"
#include "graph.hpp"
#include "solution.hpp"
#include <cmath>
#include <time.h>

class multiarranque : public algoritmo{

std::vector<solution> solutions_;
  int RCL_size = 3;
  const int ITERATIONS = 1000;
  const int IMPROVEMENT = 50;
  graph grafo;

  void set_graph(graph &g){
    grafo = g;
    // grafo.write();
  }

  void solve(graph &g){
    srand(time(NULL));
    set_graph(g);
    solution a = execute(g);
    a.write();
  }

  std::vector<int> preprocess(graph &g){
    std::vector<int> aux;
    bool positive = true;
    for(int i = 0; i < g.get_nodes(); i++){
      int cont = 0;
      for(int j =  0; j < g.get_nodes(); j++){
        if(g.get_item(i,j) >= 0){
          aux.push_back(i);
          break;
        }
      }
    }
    return aux;
  }

  solution execute(graph &g){
    set_graph(g);
    std::vector<int> s = preprocess(g);
    int cont = 0;
    int noChange = 0;
    float mean = std::numeric_limits<float>::min();
    while(cont != ITERATIONS && noChange != IMPROVEMENT){
      std::vector<int> sol = constructor(s);
      // std::cout << "sol: ";write(sol);
    // std::cout << "s: "; write(s);

      sol = local_search(sol);
      // std::cout << "getmd: " << getMd(sol) << "\n";
      if(getMd(sol) > mean) {
        mean = getMd(sol);
        s = sol;
        noChange = 0;
      } else {
        noChange++;
      }
      cont++;
      // std::cout << "mean:" << mean << "\n";
    }
    return solution(s, mean);

  }

  std::vector<int> constructor(std::vector<int> s){
   
    std::vector<int> sol;
    std::vector<int> cand = get_candidates(sol);
    int size = (rand() % (grafo.get_nodes() - 2)) + 2;
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

  std::vector<int> get_candidates(std::vector<int> sol){
    std::vector<int> cand;
    for(int i = 0; i < grafo.get_nodes(); i++){
      cand.push_back(i);
    }
    return cand;
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

   int find_k(std::vector<int> actualSolution) {
    std::vector<int> kVertex;
    kVertex.push_back(-1);
    float current = getMd(actualSolution);
    for(int i = 0; i < actualSolution.size(); i++) {
      const int vertex = actualSolution[i];
      actualSolution.erase(actualSolution.begin() + i);
      float testValue = getMd(actualSolution); 
      actualSolution.insert(actualSolution.begin() + i, vertex);
      if(testValue > current) {
        current = testValue;
        kVertex.clear();
        kVertex.push_back(i);
      } else if(testValue == current) {
        kVertex.push_back(i);
      }
    }
    //std::cout << kVertex.size() << std::endl;
    int selectedK = rand() %  (kVertex.size());
    //std::cout << selectedK << std::endl;
    return kVertex[selectedK]; 
  }

  /* Funcion que calcula la media de dispersión de un conjunto de nodos*/
  float getMd(std::vector<int> s) {
    float sum;

    if(s.size() == 0){
      std::cout << "cero\n";
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

   /*Funcion que escribe un vector*/
  void write(std::vector<int> s){
    for(int i = 0; i < s.size(); i++){
      std::cout << s[i] << " ";
    }
    std::cout << "\n";
  }
};