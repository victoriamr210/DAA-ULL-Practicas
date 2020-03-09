#pragma once
#include <iostream>
#include <vector>
#include "problem.hpp"

class quicksortS: public solution{
  private:
    std::vector<int>* v_;
    
  public:
    quicksortS(){}
    virtual ~quicksortS();
    void solve_s(void);
    void combine(std::pair<solution*,solution*> subS);
    solution* getInstance(void);
    // int size(void);
    void set(std::vector<int>* v); 
    // std::vector<int> get_vector(void);
    // void set_values(std::pair<solution *, solution *> subS);

};