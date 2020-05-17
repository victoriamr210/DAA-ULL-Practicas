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

class Node {
  private: 
    std::vector<int> sol_;
    int last;
    float value_;
    float upperBound_;
    bool expanded_;
    bool isPruned_;
    bool isSolution_;
    int depth_;
  
  public:
    Node(){}

    Node(float v, float ub){
      value_ = v;
      upperBound_ = ub;
      isPruned_ = false;
      expanded_ = false;
      isSolution_ = false;
    }

    float get_value(void){
      return value_;
    }

    void set_value(float v){
      value_ = v;
    }

    void set_pruned(bool p){
      isPruned_ = p;
    }
    void set_solution(bool p){
      isSolution_ = p;
    }

    void set_expanded(bool e){
      expanded_ = e;
    }

    bool get_expanded(void){
      return expanded_;
    }

    bool get_pruned(void){
      return isPruned_;
    }
    bool get_solution(void){
      return isSolution_;
    }
    

    void set_sol(std::vector<int> sol){
      sol_ = sol;
    }

    std::vector<int> get_sol(void){
      return sol_;
    }

    float get_UB(void) {
      return upperBound_;
    }

    void push (int node) {
      sol_.push_back(node);
    }

    void write(void){
      for(int i = 0; i< sol_.size(); i++){
        std::cout << sol_[i] << " ";
      }
      std::cout << " UB:" << upperBound_;
      std::cout << " value: " << value_ << "\n";
      std::cout << "\n";
    }

};