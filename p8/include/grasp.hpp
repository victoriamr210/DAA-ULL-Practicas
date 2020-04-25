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

/**
 * @brief Clase que implementa el algortimo GRASP
 * 
 */
class GRASP : public algoritmo{
  /*Tamaño de la RCL*/
  int RCL_size = 3;
  /*Maximo de iteraciones*/
  const int ITERATIONS = 1000;
  /*Maixmo de iteraciones sin mejora*/
  const int IMPROVEMENT = 50;
  /*Matriz de distancias*/
  graph grafo;
  /**
   * @brief Setter de la matriz de distancias
   * 
   * @param g matriz de distancias
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
    // std::cout << "s: "; write(s);
    int cont = 0;
    int noChange = 0;
    float mean = std::numeric_limits<float>::min();
    while(cont != ITERATIONS && noChange != IMPROVEMENT){
      std::vector<int> sol = constructor(s);  // solucion generada en la fase de construccion
      // std::cout << "sol: ";write(sol);
    // std::cout << "s: "; write(s);

      sol = local_search(sol); //busqueda local de la solucion construida
      // std::cout << "getmd: " << getMd(sol) << "\n";
      if(getMd(sol) > mean) { //actualizamos media si es mayor
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
   * @param s 
   * @return std::vector<int> 
   */
  std::vector<int> constructor(std::vector<int> s){
   
    int n = grafo.get_nodes();  //numero de nodos totales
    // std::cout << "n:" << n << "\n";
    int k = rand() % (n-2) + 2; // numero aleatorio de iteraciones
    // std::cout << "k:" << k << "\n";
    std::vector<int> sol;
    sol.push_back(rand() % grafo.get_nodes()); //inicializamos en vector con un nodo aleatorio
    // while(k < n){
      // std::cout 
    for(int i = 0; i < k; i++){
      std::vector<int> rcl = buildRCL(sol); //construimos la RCL
      int element = select_random(rcl); //elegimos un elemento aleatorio
      sol.push_back(element); //lo guardamos
    }
    return sol;
  }

  /**
   * @brief Funcion que genera una lista de candidatos restrigida
   * 
   * @param s lista de nodos
   * @return std::vector<int> 
   */
  std::vector<int> buildRCL(std::vector<int> s){
    int max = std::numeric_limits<int>::min(); //inicalizamos el max
    std::vector<int> cand = get_candidates(s); //generamos los canditatos
    std::vector<int> aux;
    std::vector<float> media; //vector donde se almacenan las media por cada nodo
    int index;
    float alfa = 0.3;
    // for(int i = 0; i < RCL_size; i++){
    for(int i = 0; i < cand.size(); i++){
      s.push_back(cand[i]); 
      float mean = getMd(s); //generamos la media de la solucion
      s.pop_back();
      bool found = false;

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
    int valor = aux.size() / (1 / alfa); // valor para elegir los valores que se encuentran el el 30% mas alto
    valor = valor == 0 ? 1 : valor;
    std::copy(aux.begin(), aux.begin() + valor , std::back_inserter(aux2));
    //  std::vector<int> aux2(aux.begin(), aux.begin()+RCL_size);
    // std::cout << "rcl: "; write(aux2);

    return aux2;
  }

  /**
   * @brief Funcion que selecciona un elemento aleatorio
   * 
   * @param rcl lista de nodos
   * @return int 
   */
  int select_random(std::vector<int> rcl){
    if(rcl.size() > 1){
      int index = rand() % rcl.size();
      return rcl[index];
    }

    return rcl[0];
  }

  /**
   * @brief Funcion que elimina un elemento de un vector
   * 
   * @param s vector
   * @param num elemento a eliminar
   * @return std::vector<int> 
   */
  std::vector<int> delete_item(std::vector<int> s, int num){
    s.erase(std::find(s.begin(), s.end(), num));
    return s;
  }

  /**
   * @brief Genera una lista de candidatos no incluidos en una solucion
   * 
   * @param sol lista de nodos inicial
   * @return std::vector<int> 
   */
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

  /**
   * @brief Funcion que implementa una busqueda local de una solucion
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
   * @brief Funcion que encuentra un nodo k a eliminar que maximice la meida
   * 
   * @param sol 
   * @return int 
   */
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

  /**
   * @brief Funcion que calcula la media de dispersión de un conjunto de nodos
   * 
   * @param s Lista de nodos en la solucion
   * @return float 
   */
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