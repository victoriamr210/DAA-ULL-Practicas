#pragma once
#include <iostream>
#include "problem.hpp"
#include <vector>

class Solution{
  private:
    std::vector<int> sol_;
    Problem p_;
    int time_;
  
  public:
    Solution(Problem& p, std::vector<int> sol) {
      p_ = p;
      sol_ = sol;
    }
    void set_time(int time){
      time_ = time;
    }

    void write(void){

      for(int i = 0; i < sol_.size(); i++){
        std::cout << "Vector " << i+1 << " ";
        for(int j = 0; j < p_.get_dimension(); j++){
          std::cout << p_.get_item(sol_[i], j) << " ";
        }
      std::cout << "\n";
      }
      std::cout << "Tiempo de ejecucion: " << time_ << " microsegundos\n";
    }
};