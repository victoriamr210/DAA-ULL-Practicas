#pragma once
#include <iostream>
#include "problem.hpp"
#include <vector>

class Solution{
  private:
    std::vector<int> sol_;
    Problem p_;
    int time_;
    float dis_;
  
  public:
    Solution(){}
    Solution(Problem& p, std::vector<int> sol, float dis) {
      p_ = p;
      sol_ = sol;
      dis_ = dis;
    }
    void set_time(int time){
      time_ = time;
    }

    std::vector<int> get_vector(void){
      return sol_;
    }

    float get_value() {
      return dis_;
    }

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