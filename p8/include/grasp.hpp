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
    // std::cout << "s: "; write(s);
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
   
    // int size = gra;
    int n = grafo.get_nodes();
    // std::cout << "n:" << n << "\n";
    int k = rand() % (n-2) + 2;
    // std::cout << "k:" << k << "\n";
    std::vector<int> sol;
    sol.push_back(rand() % grafo.get_nodes());
    // while(k < n){
      // std::cout 
    for(int i = 0; i < k; i++){
      std::vector<int> rcl = buildRCL(sol);
      int element = select_random(rcl);
      sol.push_back(element);
    }
    return sol;
  }

  std::vector<int> buildRCL(std::vector<int> s){
    int max = std::numeric_limits<int>::min();
    std::vector<int> cand = get_candidates(s);
    std::vector<int> aux;
    std::vector<float> media;
    int index;
    float alfa = 0.3;
    std::vector<int> saved;
    // for(int i = 0; i < RCL_size; i++){
    for(int i = 0; i < cand.size(); i++){
      s.push_back(cand[i]);
      float mean = getMd(s);
      s.pop_back();
      bool found = false;

      int pos = 0;
      for (int j = 0; j < media.size(); j++) {
        if (mean < media[j]) {
          pos++;
        }
      }
      media.insert(media.begin() + pos, mean);
      aux.insert(aux.begin() + pos, cand[i]);
    }
    
    std::vector<int> aux2;
    int valor = aux.size() / (1 / alfa);
    valor = valor == 0 ? 1 : valor;
    std::copy(aux.begin(), aux.begin() + valor , std::back_inserter(aux2));
    //  std::vector<int> aux2(aux.begin(), aux.begin()+RCL_size);
    // std::cout << "rcl: "; write(aux2);

    return aux2;
  }

  int select_random(std::vector<int> rcl){
    if(rcl.size() > 1){
      int index = rand() % rcl.size();
      return rcl[index];
    }

    return rcl[0];
  }

  std::vector<int> delete_item(std::vector<int> s, int num){
    s.erase(std::find(s.begin(), s.end(), num));
    return s;
  }

  std::vector<int> get_candidates(std::vector<int> sol){
    std::vector<int> cand;
    for(int i = 0; i < grafo.get_nodes(); i++){
      cand.push_back(i);
    }
    for(int i = 0; i < sol.size(); i++){
      cand.erase(std::find(cand.begin(), cand.end(), sol[i]));
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
    for(int i = 0; i < s.size(); i++){
      for(int j = i + 1; j < s.size(); j++){
        sum += grafo.get_item(s[i],s[j]);

      }
    // std::cout << "\n";
    }
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