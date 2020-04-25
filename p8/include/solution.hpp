#pragma once
#include <iostream>
#include <vector>

/**
 * @brief Clase que implementa una solucion
 * 
 */
class solution {
  private:
    /*Conjunto de nodos de la solucion*/
    std::vector<int> sol_;
    /*Media final*/
    float mean_;
    /*Tiempo de ejecucion*/
    int time_;
  public:
    solution(){} //cnonstructor por defecto
    /**
     * @brief Constructor
     * 
     * @param s conjunto de nodos
     * @param mean media final
     */
    solution(std::vector<int> s, float mean) {
      sol_ = s;
      mean_ = mean;
    }
    /**
     * @brief Setter del tiempo de ejecucion
     * 
     * @param time 
     */
    void set_time(int time){
      time_ = time;
    }

    /**
     * @brief Imprime la solucion por pantalla
     * 
     */
    void write(void) {
      std::cout << "Conjunto: ";
      for(int i = 0; i < sol_.size(); i++){
        std::cout << sol_[i] << " ";
      }

      std::cout << "\nMedia: " << mean_ << "\n";
      std::cout << "Tiempo de ejecucion: " << time_ << " microsegundos\n";
    }

};