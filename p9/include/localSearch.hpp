#pragma once
#include <iostream>
#include "solution.hpp"
#include "strategy.hpp"
#include "problem.hpp"
#include "voraz.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <limits>
#include <chrono>

/**
 * @brief Clase localSearch, implementa un algoritmo de búsqueda local
 * dada una solución inicial para resolver el problema
 * 
 */
class localSearch : public algorithm{
  Problem p_; //problema actual
  int M; //tamaño de solución
  public:
  Solution initial; //solución incial
  /**
   * @brief Constructor dado un tamaño de solución y solución inicial
   * 
   * @param m tamaño de solución
   * @param i solución inicial
   */
  localSearch(int m, Solution i) {
    M = m;
    initial = i;
  }

  /**
   * @brief Set el problema actual
   * 
   * @param p 
   */
  void set_problem(Problem& p){
    p_ = p;
  }

  /**
   * @brief Función que inicia la ejecución y muestra la solución
   * 
   * @param p Problema actual
   * @return Solution 
   */
  Solution solve(Problem& p){
    srand(time(NULL));
    set_problem(p);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::vector<int> sol = initial.get_vector();
    Solution s = execute(sol);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    s.set_time(duration);
    s.write();
    return s;
  }

  /**
   * @brief Función que lleva a acabo la ejecución del algoritmo
   * 
   * @return Solution 
   */
  Solution execute(std::vector<int> sol){
    std::vector<int> solution = sol;
    float distance = get_total(sol);
    bool change = true;
    while (change) {
      std::vector<int> aux = local_search(solution);
      if (get_total(aux) > distance) {
        solution = aux;
        distance = get_total(aux);
      } else {
        change = false;
      }
    }
    return Solution (p_, solution, distance);

  }

  /**
   * @brief Función que implementa la busqueda local mediante un intercambio
   * de elementos, se intercambia sólo uno
   * 
   * @param sol solución actual
   * @return std::vector<int> 
   */
  std::vector<int> local_search(std::vector<int> sol){
    float distance = get_total(sol);
    std::vector<int> optimum;
    std::vector<int> aux = sol;
    bool change = false;
    do {
      std::vector<int> cand = get_candidates(aux);
      change = false;
      for(int i = 0; i < aux.size(); i++){
        int auxItem = aux[i];
        for (int j = 0; j < cand.size(); j++){
          aux[i] = cand[j];
          float auxDistance = get_total(aux);
          if (auxDistance > distance) {
            distance = auxDistance;
            optimum = aux;
            change = true;
          }
        }
        aux[i] = auxItem;
      }
    } while (change);
    return optimum;
  }

  /**
   * @brief Devuelve conjunto de elementos no incluidos en la solución
   * 
   * @param sol 
   * @return std::vector<int> 
   */
  std::vector<int> get_candidates(std::vector<int> sol){
    std::vector<int> cand;
    for(int i = 0; i < p_.get_elements(); i++){
        cand.push_back(i);
    }
    for(int i = 0; i < sol.size(); i++){
      cand.erase(std::find(cand.begin(), cand.end(), sol[i]));
    }
    return cand;
  }

  /**
   * @brief Devuelve la diversión total dada una solución 
   * 
   * @param sol Conjunto solución
   * @return float 
   */
  float get_total(std::vector<int> sol){
    float aux = 0;
    for(int i = 0; i < sol.size(); i++) {
      for(int j = i+1; j < sol.size(); j++) {
        aux += p_.get_distance(sol[i], sol[j]);
      }
    }
    return aux;
  }
};