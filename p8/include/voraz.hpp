#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"

/*Clase que implementa el algoritmo constructivo voraz*/
class voraz : public algoritmo{
  /**
   * @desc vector de nodos incluidos en la solucion
   **/
  std::vector<solution> solutions_;
  void solve(graph &g) {
    // for (int i = 0; i < 20; i++) {
    //   solutions_.push_back(execute(g));
    // }
    solution a = execute(g);
    a.write();

  }

  /* Funcion principal que implementa el algortimo voraz*/
  solution execute(graph &g){

    std::vector<int> s;
    std::pair<int,int> p = g.maximum();
    // pairs_.push_back(std::make_pair(p.first, p.second));
    s.push_back(p.first);
    s.push_back(p.second);
    int cont = 0;
    float mean = g.get_item(p.first, p.second) / 2;
    //  for (int i = 0; i < s.size(); i++) {
      // std::cout << "i:" << s[i] << " ";
    // }
    // std::cout << "solve mean: " << mean << "\n";
    std::vector<int> s_prima;
    while(s_prima.size() != s.size() /*&& cont < g.get_nodes()*/) {
      // std::cout << "hello\n";
      // std::cout << "1:" << s.size() << " 2:" << s_prima.size() << "\n";
      s_prima = s;
      int node = find_k(s, g, mean); 
      if (node == -1) {
        break;
      } else {
        s.push_back(node);
      }
      cont++;
      
    }
    std::cout << "final:" << mean << "\n";
    return solution(s, mean);
    // g.set_sol(s, mean);

  }

  /* Funcion que encuentra un vertica k que maximize la media de dispersión*/
  int find_k(std::vector<int> &s, graph &g, float &mean) {
    int node = -1;
    float aux_mean = mean;
    float aux_mean2;
    // std::cout << "\n\ninical:" << mean << "\n";
    // for (int i = 0; i < s.size(); i++) {
    //   std::cout << "i:" << s[i] << " ";
    // }
    // std::cout << "\n";
    // for (int i = 0; i < s.size(); i++) {
      for (int j = 0;  j < g.get_nodes(); j++){
        
            // std::cout << "j: " << j << "\n";
        if (valid(s,j)) {
          std::vector<int> aux = s;
          aux.push_back(j);
          // std::cout << "array: ";
          // for (int k = 0; k < aux.size(); k++){
            // std::cout << aux[k] << " ";
          // }
          // std::cout << "\n";
          aux_mean2 = getMd(aux, g);
          // aux_mean2 = get_mean(mean, s.size(), g.get_item(i,j));
            // std::cout << "aux:" << aux_mean2 <<  " mean:" << aux_mean << "\n";
          if (aux_mean2 >= aux_mean) {
            node = j;
            aux_mean = aux_mean2;
          }
          // if ((mean + (g.get_item(i,j) / (s.size() +1))) >= aux_mean) {
            // aux_mean = mean + (g.get_item(i,j) / (s.size()+1));
          // }
        }
      }
    // }
      // std::cout << "node: " <<  node << "\n";
    if(aux_mean >= mean) {
      mean = aux_mean;
      return node;
    } else {
      return -1;
    }
  }

  /* Funcion que calcula la media de dispersión de un conjunto de nodos*/
  float getMd(std::vector<int> s, graph &g) {
    float sum;
    for(int i = 0; i < s.size(); i++){
      for(int j = i + 1; j < s.size(); j++){
        // std::cout << "i:" << i << " j:" << j << " ";
        // std::cout << g.get_item(i,j) << "\n";
        sum += g.get_item(s[i],s[j]);

      }
    // std::cout << "\n";
    }
    return sum / s.size();
  }

  /*Funcion que comprueba si el nodo candidato existe en la solución o no*/
  bool valid(std::vector<int> &s, int j) {
    for(int k = 0; k < s.size(); k++){
      if(s[k] == j){
        return false;
      }
    }
    return true;
  }

  float get_mean(float aux_mean, int size, float next) {
    return (aux_mean * size + next) / (size + 1);
  }
};