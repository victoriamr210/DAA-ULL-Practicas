#pragma once
#include <iostream>
#include "solution.hpp"
#include "strategy.hpp"
#include "problem.hpp"
#include "node.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <limits>
#include <chrono>

/**
 * @brief Clase RyP, implementa el algoritmo de ramificación y poda para resolver
 * el problema
 * 
 */
class RyP : public algorithm {
  Problem p_; // Problema actual
  int M; //tamaño de solucion
  Solution inferior; //solucion que nos da la cota inferior
  float lower_bound; // cota inferior
  std::vector<Node> tree_; //vector que representa el árbol
  std::vector<int> activeNodes; //lista de nodos activos
  std::vector<int> currentSol; //mejor solución encontrada hasta el momento
  bool minCota; //booleano que indica la estrategia para expandir
  int currentK; 

  public:
  /**
   * @brief Constructor dado un tamaño de solución, una solución de donde obtener
   * la cota inferior y una estrategia de expansión
   * 
   * @param m 
   * @param i 
   * @param min 
   */
  RyP(int m, Solution i, bool min){
    M = m;
    inferior = i;
    lower_bound = inferior.get_value();
    minCota = min;
  }

  /**
   * @brief Setter del problema actual
   * 
   * @param p 
   */
  void set_problem(Problem& p){
    p_ = p;
  }

  /**
   * @brief Devuelve los elementos no incluidos en la solución
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
   * @brief Función que inicia la ejecución y muestra la solución
   * 
   * @param p Problema actual
   * @return Solution 
   */
  Solution solve(Problem& p){

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
  Solution execute(){

    initialize_tree();
    currentK++;;
    while(activeNodes.size() != 0){
      prune();
      int pos = get_minimum();
      if(pos != -1){
        expand(pos);
        check_for_sol();
      }else{
        break;
      }
    }
    float dis = get_total(currentSol);
    return Solution(p_, currentSol, dis);
  }

  /**
   * @brief Función que inicializa el árbol, genera el primer nivel de este
   * 
   */
  void initialize_tree(void){
    int n = p_.get_elements();
    for(int i = 0; i < (n-(M-1)); i++){
      std::vector<int> s;
      s.push_back(i);
      float upb = calculate_UB(s);
      Node aux(0, upb);
      aux.set_sol(s);
      tree_.push_back(aux);
      activeNodes.push_back(tree_.size() - 1);
    }
  }

  /**
   * @brief Funcion que calcula la cota superior dada una solucíon parcial
   * 
   * @param s 
   * @return float 
   */
  float calculate_UB(std::vector<int> s){
    // std::cout << "upper\n";
    std::vector<int> unSel = get_candidates(s);
    std::vector<float> upperB2;
    std::vector<float> upperB3;
    for(int i = 0; i < s.size(); i++){
      for(int j = 0; j < unSel.size(); j++){
        float distance = p_.get_distance(s[i], unSel[j]);
        int pos = 0;
        for (int k = 0; k < upperB2.size(); k++) {
          if (distance < upperB2[k]){
          pos++;
          }
        }
        upperB2.insert(upperB2.begin() + pos, distance);
      }
    }
    int k = s.size();
    int size = k * (M - k);
    float UB2=0;
    for(int i = 0; i < size; i++){
      UB2 += upperB2[i];
    }

    for (int i = 0; i < unSel.size(); i++){
      for (int j = i+1; j < unSel.size(); j++){
        float distance = p_.get_distance(unSel[i], unSel[j]);

        int pos = 0;
        for (int k = 0; k < upperB3.size(); k++) {
          if (distance < upperB3[k]){
            pos++;
          }
        }
        upperB3.insert(upperB3.begin() + pos, distance);
      }
    }
    
    size = 0;
    for (int i = M - k - 1; i > 0; i--) {
      size += i;
    }
    float UB3=0;
    for(int i = 0; i < size; i++){
      UB3 += upperB3[i];
    }
    // std::cout << UB2 + UB3 << "\n";
    return UB2 + UB3;
  }

  /**
   * @brief Funcion que elige elemento a expandir según la estrategia de expansión
   * 
   * @return int 
   */
  int get_minimum(void) {
    int pos = -1;
    if(minCota){
      float min = std::numeric_limits<float>::max();
      for(int i = 0; i < tree_.size(); i++){
        if(!tree_[i].get_pruned() && !tree_[i].get_expanded() && !tree_[i].get_solution()){
          // std::cout << "min\n";
          float auxDis = tree_[i].get_UB();
          if ((auxDis < min)) {
            min = auxDis;
            pos = i;
          }
        }
      }
    }else {
      int deepK = -1;
      for(int i = 0; i < tree_.size(); i++){
        if (!tree_[i].get_pruned() && !tree_[i].get_expanded() && !tree_[i].get_solution()){
          int size = tree_[i].get_sol().size();
          if (size > deepK){
            deepK = size;
            pos = i;
          }
        }
      } 
    }

    return pos;
  }

  /**
   * @brief Función que realiza la expansión de un nodo dado.
   * 
   * @param pos 
   */
  void expand(int pos){
    tree_[pos].set_expanded(true);
    // if (std::find(activeNodes.begin(), activeNodes.end(), pos) != activeNodes.end()){
      activeNodes.erase(std::find(activeNodes.begin(), activeNodes.end(), pos));
    // }
      int currentK = tree_[pos].get_sol().size();
      int initial = tree_[pos].get_sol().back() + 1;
      std::vector<int> partialSol = tree_[pos].get_sol();
      int n = p_.get_elements();
    
      for (int i = initial; i < (n-(M-currentK)); i++){
        std::vector<int> s = partialSol;
        s.push_back(i);
        float upb = calculate_UB(s);
        float value = get_total(s);
        Node aux(value, upb);
        aux.set_sol(s);
        tree_.push_back(aux);
        activeNodes.push_back(tree_.size() - 1);
      }
  }

  /**
   * @brief Función que poda todos los nodos cuyo valor máximo es menor a la
   * cota inferior
   * 
   */
  void prune(void) {
    for(int i = 0; i < tree_.size(); i++){
      float up = tree_[i].get_value() + tree_[i].get_UB();
      if (up < lower_bound) {
        tree_[i].set_pruned(true);
        if (std::find(activeNodes.begin(), activeNodes.end(), i) != activeNodes.end()){
          activeNodes.erase(std::find(activeNodes.begin(), activeNodes.end(), i));
        }
      }
    }
  }

  /**
   * @brief Funcion que busca soluciones completas para que no puedan seguir expandiendo
   * 
   */
  void check_for_sol(void){
    for(int i = 0; i < tree_.size(); i++){
      if(tree_[i].get_sol().size() == M) {
        tree_[i].set_solution(true);
        // std::cout << "hola\n";
        std::vector<int> s  = tree_[i].get_sol();
        if(get_total(s) >= lower_bound) {
          lower_bound = get_total(s);
          currentSol = s;
        }
      }
    }
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

  void write(void){
    for(int i = 0; i < tree_.size(); i++){
      tree_[i].write();
    }
  }
  
};