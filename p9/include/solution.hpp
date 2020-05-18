#pragma once
#include <iostream>
#include "problem.hpp"
#include <vector>

/**
 * @brief Clase Solution, representará la solución del problema
 * tendrá en conjunto de vectores, así como, el valor de diversión y 
 * el tiempo de ejecución
 * 
 */
class Solution{
  private:
    std::vector<int> sol_; //conjunto de vectores de la solución
    Problem p_; //problema actual
    int time_; //tiempo de ejecución
    float dis_; //diversión
  
  public:
    /**
     * @brief Constructor por defecto
     * 
     */
    Solution(){}
    /**
     * @brief Constructor con parámetros
     * 
     * @param p Problema
     * @param sol Conjunto solución
     * @param dis Valor de la diversión
     */
    Solution(Problem& p, std::vector<int> sol, float dis) {
      p_ = p;
      sol_ = sol;
      dis_ = dis;
    }
    /**
     * @brief Set tiempo de ejecución
     * 
     * @param time 
     */
    void set_time(int time){
      time_ = time;
    }
    /**
     * @brief Getter del conjutno solución
     * 
     * @return std::vector<int> 
     */
    std::vector<int> get_vector(void){
      return sol_;
    }

    float get_value() {
      return dis_;
    }

    /**
     * @brief Función para escribir la solución
     * 
     */
    void write(void){

      for(int i = 0; i < sol_.size(); i++){
        std::cout << "Vector " << sol_[i] << " ";
        for(int j = 0; j < p_.get_dimension(); j++){
          std::cout << p_.get_item(sol_[i], j) << " ";
        }
      std::cout << "\n";
      }
      std::cout << "Distancia total: " << dis_ << "\n";
      std::cout << "Tiempo de ejecucion: " << time_ << " microsegundos\n";
    }
};