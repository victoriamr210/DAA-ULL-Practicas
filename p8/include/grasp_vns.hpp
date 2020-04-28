#pragma once
#include "graph.hpp"
#include "strategy.hpp"
#include "solution.hpp"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <limits>
#include <chrono>

/*********************************
 * MODIFICACION
 *********************************/

class graspVns :public algoritmo{
  /*Maximo de iteraciones*/
  const int ITERATIONS = 1000;
  /*Maixmo de iteraciones sin mejora*/
  const int IMPROVEMENT = 50;
  int RCL_size = 2;
  graph grafo;
  bool greedy_;

   void set_graph(graph &g){
    grafo = g;
    // grafo.write();
  }

  void solve(graph &g, bool greedy){
    srand(time(NULL));
    set_graph(g);
    greedy_ = greedy;
    auto t1 = std::chrono::high_resolution_clock::now();
    solution a = execute(g);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    a.set_time(duration);
    a.write();
  }

  void build_list(std::vector<int> &s, int size){
    s.resize(size);
    for(int i = 0; i < size; i++){
      s[i] = i;
    }
  }

   solution execute(graph &g){
    set_graph(g);
    std::vector<int> s_best;
    build_list(s_best, grafo.get_nodes());
    // std::cout << "s: "; write(s);
    std::vector<int> s = constructor(s_best); 
    float mean = std::numeric_limits<float>::min();
    int k = 1;
    while(k <= 4) {
      int i = 1;
      std::vector<int> s_prima2 = change(s, k);
      while(i <= 4){
        std::vector<int> s_prima = change(s,k);
        s_prima = local_search(s_prima);
        if (getMd(s_prima) > getMd(s_prima2)){
          s_prima2 = s_prima;
        }
        i++;
      }
      if (getMd(s_prima2) > getMd(s)){
        s = s_prima2;
        k = 1;
      } else {
        k++;
      }
    }
    if (getMd(s) > getMd(s_best)) {
      s_best = s;
    }

    mean = getMd(s_best);
    return solution(s_best, mean);

  }

  std::vector<int> change(std::vector<int> s, int k) {
    std::vector<int> aux = get_candidates(s);
    for(int i = 0; i < k; i++){
      int spos = rand() % s.size();
      s.erase(s.begin() + spos);
      int auxPos = rand() % aux.size();
      s.push_back(aux[auxPos]);
      aux.erase(aux.begin() + auxPos);
    }
    return s;
  }

    std::vector<int> local_search(std::vector<int> sol){
    bool flag = true;
    while(flag){
      flag = false;
      int k;
      if(greedy_){
        k = find_k(sol); //buscmos un indice k a eliminar que maximice la media
      } else {
        k =  find_k_anxious(sol); //buscmos un indice k a eliminar que maximice la media
      }
      std::vector<int> aux;
      if(k != -1){
        flag=true;
        sol.erase(sol.begin() + k); //elimanos el nodo de la solucion
      } 
    }
    return sol;
  }

  std::vector<int> constructor(std::vector<int> s){
   
    int n = grafo.get_nodes();  //numero de nodos totales
    // std::cout << "n:" << n << "\n";
    int k = rand() % (n-2) + 2; // numero aleatorio de iteraciones
    // std::cout << "k:" << k << "\n";
    std::vector<int> sol;
    sol.push_back(rand() % grafo.get_nodes()); //inicializamos en vector con un nodo aleatorio
      // std::cout 
    for(int i = 0; i < k; i++){
      std::vector<int> rcl = buildRCL(sol); //construimos la RCL
      int element = select_random(rcl); //elegimos un elemento aleatorio
      sol.push_back(element); //lo guardamos
    }
    return sol;
  }

  std::vector<int> buildRCL(std::vector<int> s){
    int max = std::numeric_limits<int>::min(); //inicalizamos el max
    std::vector<int> cand = get_candidates(s); //generamos los canditatos
    std::vector<int> aux;
    std::vector<float> media; //vector donde se almacenan las media por cada nodo
    float alfa = 0.3;
    for(int i = 0; i < cand.size(); i++){
      s.push_back(cand[i]); 
      float mean = getMd(s); //generamos la media de la solucion
      s.pop_back();

      int pos = 0;
      for (int j = 0; j < media.size(); j++) {
        if (mean < media[j]) {
          pos++; //aumentamos la posicion respectiva al vector
        }
      }
      media.insert(media.begin() + pos, mean); //insertamos el valor de la media en la posicion correspondiente
      aux.insert(aux.begin() + pos, cand[i]); //insertamos el nodo segun su media
    }
    
    std::vector<int> aux2;
    for(int i = 0; i < RCL_size; i++){
      aux2.push_back(aux[i]);
    }
    //  std::vector<int> aux2(aux.begin(), aux.begin()+RCL_size);
    // std::cout << "rcl: "; write(aux2);

    return aux2;
  }

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
    return sum / s.size();
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

  int select_random(std::vector<int> rcl){
    if(rcl.size() > 1){
      int index = rand() % rcl.size();
      return rcl[index];
    }

    return rcl[0];
  }

   int find_k(std::vector<int> sol) {
    std::vector<int> aux;
    aux.push_back(-1);
    float current = getMd(sol); // generamos la media de la solucion actual
    for(int i = 0; i < sol.size(); i++) {
      const int vertex = sol[i];
      sol.erase(sol.begin() + i); //probamos eliminando un nodo
      float testValue = getMd(sol); //generamos su media
      sol.insert(sol.begin() + i, vertex);
      if(testValue > current) { //actualizamos la media si es necesario
      // return i;
        current = testValue; 
        aux.clear();
        aux.push_back(i); 
      } else if(testValue == current) {
        aux.push_back(i); //si el valor de la media es igual lo guardamos el nodo en un vector
      }
    }
    //std::cout << aux.size() << std::endl;
    int index = rand() %  (aux.size()); //elegimos un nodo aleatorio de los posibles
    //std::cout << index << std::endl;
    return aux[index]; 
  }

  int find_k_anxious(std::vector<int> sol) {
    std::vector<int> aux;
    aux.push_back(-1);
    float current = getMd(sol); // generamos la media de la solucion actual
    for(int i = 0; i < sol.size(); i++) {
      const int vertex = sol[i];
      sol.erase(sol.begin() + i); //probamos eliminando un nodo
      float testValue = getMd(sol); //generamos su media
      sol.insert(sol.begin() + i, vertex);
      if(testValue > current) { //actualizamos la media si es necesario
        return i; 
      }
    }
    return -1;
  }
};