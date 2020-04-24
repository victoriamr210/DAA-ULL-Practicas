#pragma once
#include <iostream>
#include <vector>

class solution {
  private:
    std::vector<int> sol_;
    float mean_;
  public:
    solution(){}
    solution(std::vector<int> s, float mean) {
      sol_ = s;
      mean_ = mean;
    }

    void write(void) {
      std::cout << "conjunto: ";
      for(int i = 0; i < sol_.size(); i++){
        std::cout << sol_[i] << " ";
      }

      std::cout << "\nmedia:" << mean_ << "\n";
    }

};