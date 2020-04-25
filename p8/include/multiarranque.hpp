#include <iostream>
#include "strategy.hpp"
#include "graph.hpp"
#include "solution.hpp"
#include <cmath>
#include <time.h>
/**
 * @brief Clase que implementa un algoritmo de multiarranque
 * 
 */
class multiarranque : public algoritmo{

  /*Iteraciones maximas*/
  const int ITERATIONS = 1000;
  /*Iteraciones max sin mejora*/
  const int IMPROVEMENT = 50;
  /*Matriz de distancias*/
  graph grafo;
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
  void solve(graph &g){
    srand(time(NULL));
    set_graph(g);
    auto t1 = std::chrono::high_resolution_clock::now();
    solution a = execute(g);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    a.set_time(duration);
    a.write();
  }
  /**
   * @brief Funcion que elige todos los nodos con al menos alguna arista positiva
   * 
   * @param g matriz de distancias
   * @return std::vector<int> 
   */
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
  
  /**
   * @brief Ejecucion principal del algoritmo
   * 
   * @param g matriz de distancias
   * @return solution 
   */
  solution execute(graph &g){
    set_graph(g);
    std::vector<int> s = preprocess(g);
    int cont = 0;
    int noChange = 0;
    float mean = std::numeric_limits<float>::min();
    while(cont != ITERATIONS && noChange != IMPROVEMENT){
      std::vector<int> sol = constructor(); // solucion aleatoris generada
      // std::cout << "sol: ";write(sol);
      // std::cout << "s: "; write(s);

      sol = local_search(sol); //busqueda local de la solucion construida
      // std::cout << "getmd: " << getMd(sol) << "\n";
      if(getMd(sol) > mean) {  //actualizamos media si es mayor
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
  /**
   * @brief Construye una solucion aleatoria
   * 
   * @return std::vector<int> 
   */
  std::vector<int> constructor(){
   
    std::vector<int> sol;
    std::vector<int> cand = get_candidates(sol);
    int size = (rand() % (grafo.get_nodes() - 2)) + 2; //generamos un tamaño de solucion aleatoria
    // std::cout << "cand: "; write(cand);
    while(sol.size() < size){ //insertamos nodos en la solucion hasta que lleguemos al tamaño calculado
      int element = rand() % cand.size();  
      if(std::find(sol.begin(), sol.end(), cand[element]) == sol.end()) {
        sol.push_back(element);
      }
      // std::cout << "sol: "; write(sol);
    }
    return sol;
  }
  /**
   * @brief Genera una lista de nodos candidatos
   * 
   * @param sol 
   * @return std::vector<int> 
   */
  std::vector<int> get_candidates(std::vector<int> sol){
    std::vector<int> cand;
    for(int i = 0; i < grafo.get_nodes(); i++){
      cand.push_back(i);
    }
    return cand;
  }

  /**
   * @brief Funcion que implementa la busqueda local de una solucion
   * 
   * @param sol solucion
   * @return std::vector<int> 
   */
  std::vector<int> local_search(std::vector<int> sol){
    bool flag = true;
    while(flag){
      flag = false;
      int k = find_k(sol); //buscmos un indice k a eliminar que maximice la media
      std::vector<int> aux;
      if(k != -1){
        flag=true;
        sol.erase(sol.begin() + k); //elimanos el nodo de la solucion
      } 
    }
    return sol;
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
      const int vertex = sol[i];
      sol.erase(sol.begin() + i); //probamos eliminando un nodo
      float test = getMd(sol);    //generamos su media
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
    int index = rand() % (aux.size()); //elegimos un nodo aleatorio de los posibles
    //std::cout << index << std::endl;
    return aux[index]; 
  }

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
    // if()
    return sum / s.size();
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