#include <iostream>
#include "strategy.hpp"
#include "graph.hpp"
#include "solution.hpp"
#include <cmath>
#include <time.h>


/**
 * @brief Clase VNS que implementa el agloritmo Variable Neighbourhood Search
 * 
 */
class VNS : public algoritmo{
  /*Matriz de distancias*/
  graph grafo;
  /*Iteraciones maximas*/
  const int ITERATIONS = 1000;
  /*Iteraciones sin mejora*/
  const int IMPROVEMENT = 50;
  /*Tamaño maximo del entorno*/
  const int KMAX = 3;
  bool greedy_;

  /**
   * @brief Setter de la matriz de distancias
   * 
   * @param g grafo
   */
  void set_graph(graph &g){
    grafo = g;
    // grafo.write();
  }

  /**
   * @brief Funcion principal, inicia la ejecucion
   * 
   * @param g grafo
   */
  void solve(graph &g, bool greedy){
    srand(time(NULL));
    set_graph(g);
    greedy_ = greedy;
    auto t1 = std::chrono::high_resolution_clock::now();
    solution a = execute();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    a.set_time(duration);
    a.write();
  }

  /**
   * @brief Ejecucion principal del algoritmo
   * 
   * @return solution 
   */
  solution execute(void){
    std::vector<int> cand = get_candidates();
    int size = (rand() % (grafo.get_nodes() -2)) + 2; //tamaños aleatorio de la solucion
    std::vector<int> sol = constructor(cand, size); //generamos solucion
    // std::cout <<"sol: "; write(sol);
    sol = local_search(sol); //hacemos una primera busqyeda local
    std::vector<int> s;
    // std::cout <<"sol: "; write(sol);
    float mean = getMd(sol); //generamos la media de la solucion
    int cont = 0;
    int noChange = 0;
    int k = 1;
    while(cont < ITERATIONS && noChange < IMPROVEMENT){
      k = 1;
      while(k <= KMAX){
        s = shake(cand, size, k); //solucion aleatoria que pertence al entorno
        std::vector<int> localBest = local_search(s); //busqueda local de la solucion actuañ
        float aux_mean = getMd(s);
        if(aux_mean > mean){ //actualizamos la media si es necesatio
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


  /**
   * @brief Construye una solucion aleatoria dado un tamaño y una lista de candidatos
   * 
   * @param cand lista de candidatos
   * @param size tamaño de la solucion
   * @return std::vector<int> 
   */
  std::vector<int> constructor(std::vector<int> cand, int size){
  
    std::vector<int> sol;
    while(sol.size() < size){
      int element = rand() % cand.size();
      if(std::find(sol.begin(), sol.end(), cand[element]) == sol.end()) {
        sol.push_back(element);
      }
    }
    return sol;
  }

  /**
   * @brief Funcion que implementa una busqueda local, busca un nodo para eliminar que maximice la media
   * 
   * @param sol lista de nodos de la solucion
   * @return std::vector<int> 
   */
  std::vector<int> local_search(std::vector<int> sol){
    bool flag = true;
    while(flag){
      flag = false;
      int k;
      if(greedy_) {
        k = find_k(sol); //buscmos un indice k a eliminar que maximice la media
      } else {
        k = find_k_anxious(sol); //buscmos un indice k a eliminar que maximice la media
      }
      std::vector<int> aux;
      if(k != -1){
        flag=true;
        sol.erase(sol.begin() + k); //eliminamos el nodo de la solucion
      } 
    }
    return sol;
  }

  /**
   * @brief Funcion que implementa la agitacion, dado un k se crea el tamaño del entorno
   * 
   * @param cand lista de candidatos
   * @param sol_size tamaño de la solucion
   * @param k numero de entorno
   * @return std::vector<int> 
   */
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

  /**
   * @brief Funcion que busca un nodo k a eliminar que maximice la media
   * 
   * @param sol solucion actual
   * @return int 
   */
  int find_k(std::vector<int> sol) {
    std::vector<int> aux;
    aux.push_back(-1);
    float current = getMd(sol); // generamos la media de la solucion actual
    for(int i = 0; i < sol.size(); i++) {
      const int vertex = sol[i]; //probamos eliminando un nodo
      sol.erase(sol.begin() + i); //generamos su media
      float test = getMd(sol); 
      sol.insert(sol.begin() + i, vertex);
      if(test > current) { //actualizamos la media si es necesario
        current = test;
        aux.clear();
        aux.push_back(i);
      } else if(test == current) {
        aux.push_back(i); //si el valor de la media es igual lo guardamos el nodo en un vector
      }
    }
    //std::cout << aux.size() << std::endl;
    int index = rand() %  (aux.size());
    //std::cout << index << std::endl;
    return aux[index]; 
  }

   /**
   * @brief Funcion que busca un nodo k a eliminar que maximice la media
   * 
   * @param sol solucion actual
   * @return int 
   */
  int find_k_anxious(std::vector<int> sol) {
    std::vector<int> aux;
    aux.push_back(-1);
    float current = getMd(sol); // generamos la media de la solucion actual
    for(int i = 0; i < sol.size(); i++) {
      const int vertex = sol[i]; //probamos eliminando un nodo
      sol.erase(sol.begin() + i); //generamos su media
      float test = getMd(sol); 
      sol.insert(sol.begin() + i, vertex);
      if(test > current) { //actualizamos la media si es necesario
        return i;
      }
    }
    return -1;
  }

  /* */
  /**
   * @brief Funcion que calcula la media de dispersión de un conjunto de nodos
   * 
   * @param s Lista de nodos en la solucion
   * @return float 
   */
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

  /**
   * @brief Funcion que crea una lista de candidatos
   * 
   * @return std::vector<int> 
   */
  std::vector<int> get_candidates(void){
    std::vector<int> cand;
    for(int i = 0; i < grafo.get_nodes(); i++){
      cand.push_back(i);
    }
    return cand;
  }

  /**
   * @brief Funcion que escribe un vector
   * 
   * @param s vector a escribit
   */
  void write(std::vector<int> s){
    for(int i = 0; i < s.size(); i++){
      std::cout << s[i] << " ";
    }
    std::cout << "\n";
  }
};