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
 * @brief Clase Node, representa un nodo del árbol
 * 
 */
class Node {
  private: 
    std::vector<int> sol_; //solución parcial
    float value_; //valor del nodo
    float upperBound_; //cota superior del nodo
    bool expanded_; //si esta expandido o no
    bool isPruned_; //si esta podado o no
    bool isSolution_; //si es solución o no
  
  public:
  /**
   * @brief Constructor por defecto
   * 
   */
    Node(){}

    /**
     * @brief Constructor dada un valor y una cota superior
     * 
     * @param v 
     * @param ub 
     */
    Node(float v, float ub){
      value_ = v;
      upperBound_ = ub;
      isPruned_ = false;
      expanded_ = false;
      isSolution_ = false;
    }
    /**
     * @brief Getter del valor del nodo
     * 
     * @return float 
     */
    float get_value(void){
      return value_;
    }
    
    /**
     * @brief Setter del valor de nodo
     * 
     * @param v 
     */
    void set_value(float v){
      value_ = v;
    }

    /**
     * @brief Cambia el valor de isPruned_
     * 
     * @param p 
     */
    void set_pruned(bool p){
      isPruned_ = p;
    }

    /**
     * @brief Setter de la solución actual
     * 
     * @param p 
     */
    void set_solution(bool p){
      isSolution_ = p;
    }

    /**
     * @brief Cambia el valor de expanded_
     * 
     * @param p 
     */
    void set_expanded(bool e){
      expanded_ = e;
    }

    /**
     * @brief Getter del valor expanded_
     * 
     * @return true 
     * @return false 
     */
    bool get_expanded(void){
      return expanded_;
    }

    /**
     * @brief Getter del vaor isPruned_
     * 
     * @return true 
     * @return false 
     */
    bool get_pruned(void){
      return isPruned_;
    }

    /**
     * @brief Getter del valor isSolution_
     * 
     * @return true 
     * @return false 
     */
    bool get_solution(void){
      return isSolution_;
    }
    
    /**
     * @brief Asigna la solución parcial
     * 
     * @param sol 
     */
    void set_sol(std::vector<int> sol){
      sol_ = sol;
    }

    /**
     * @brief Getter la solución parcial  
     * 
     * @return std::vector<int> 
     */
    std::vector<int> get_sol(void){
      return sol_;
    }

    /**
     * @brief Getter de la cota superior
     * 
     * @return float 
     */
    float get_UB(void) {
      return upperBound_;
    }

    /**
     * @brief Añade un elemento a la solución parcial
     * 
     * @param node 
     */
    void push (int node) {
      sol_.push_back(node);
    }

    /**
     * @brief Escribe la info del nodo en pantalla
     * 
     */
    void write(void){
      for(int i = 0; i< sol_.size(); i++){
        std::cout << sol_[i] << " ";
      }
      std::cout << " UB:" << upperBound_;
      std::cout << " value: " << value_ << "\n";
      std::cout << "\n";
    }

};