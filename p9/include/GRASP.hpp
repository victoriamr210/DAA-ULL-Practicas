#pragma once
#include <iostream>
#include "solution.hpp"
#include "strategy.hpp"
#include "problem.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <limits>
#include <chrono>

/**
 * @brief Clase GRASP, implementa un algoritmo grasp para resolver el problema
 * 
 */
class GRASP : public algorithm{
  Problem p_; //problema actual
  int M; //tamaño de solución
  const int RCL_size = 3; //tamaño de lista de candidatos
  const int ITERATIONS = 10; //número máximo de iteraciones

  public:
  /**
   * @brief Constructor dado un tamaño de solución
   * 
   * @param m 
   */
  GRASP(int m) {
    M = m;
  }

  /**
   * @brief Set del problema actual
   * 
   * @param p 
   */
  void set_problem(Problem& p){
    p_ = p;
  }

  /**
   * @brief Seleciona un elemento aleatorio de un conjunto de elementos
   * 
   * @param v 
   * @return int 
   */
  int select_random(std::vector<int> v){
    if (v.size() > 1) {
      int index = rand() % v.size();
      return v[index];
    }
    return v[0];
  }

  /**
   * @brief Función que inicia la ejecución y muestra la solución
   * 
   * @param p Problema actual
   * @return Solution 
   */
  Solution solve(Problem &p) {
    srand(time(NULL));
    set_problem(p);
    auto t1 = std::chrono::high_resolution_clock::now();
    Solution s = execute();
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
  Solution execute(void) {
    float distance = std::numeric_limits<float>::min();
    int cont = 0;
    std::vector<int> bestSol;
    std::vector<int> sol;
    while (cont != ITERATIONS) {
      std::vector<int> sol = constructor();
      sol = local_search(sol);
      float auxDistance = get_total(sol);
      if (auxDistance > distance) {
        bestSol = sol;
        distance = auxDistance;
        cont = 0;
      } 
      else {
        cont++;
      }
    }
    return Solution(p_, bestSol, distance);
  }

  /**
   * @brief Fase constructiva de grasp, genera la rcl y elige un elemento aleatorio
   * 
   * @return std::vector<int> 
   */
  std::vector<int> constructor(){
    int n = p_.get_elements();
    int k = rand() %  (n - 2) + 2;
    std::vector<int> sol;
    sol.push_back(rand() % n);
    while(sol.size() < M) {
      std::vector<int> rcl = buildRCL(sol);
      int element = select_random(rcl);
      sol.push_back(element);
    }
    return sol;
  }

  /**
   * @brief Construye la rcl dada un solución.
   * 
   * @param sol 
   * @return std::vector<int> 
   */
  std::vector<int> buildRCL(std::vector<int> sol) {
    std::vector<int> cand = get_candidates(sol);
    std::vector<int> vectors;
    std::vector<float> dis;
    for(int i = 0; i < cand.size(); i++) {
      sol.push_back(cand[i]);
      float distance = get_total(sol);
      sol.pop_back();

      int pos = 0;
      for (int j = 0; j < dis.size(); j++) {
        if (distance < dis[j]){
          pos++;
        }
      }
      dis.insert(dis.begin() + pos, distance);
      vectors.insert(vectors.begin() + pos, cand[i]);
    }

    std::vector<int> aux;
    for(int i = 0; i < RCL_size; i++){
      aux.push_back(vectors[i]);
    }

    return aux;
  }

  /**
   * @brief Función que implementa la búsqueda local mediante intercambio
   * dada una solución
   * 
   * @param sol 
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
   * @brief Devuelve los elementos no incluidos en una solución
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
  float get_total(std::vector<int> sol) {
    float aux = 0;
    for(int i = 0; i < sol.size(); i++) {
      for(int j = i+1; j < sol.size(); j++) {
        aux += p_.get_distance(sol[i], sol[j]);
      }
    }
    return aux;
  }
};