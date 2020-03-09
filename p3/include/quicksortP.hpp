#pragma once
#include <iostream>
#include <vector>
#include "problem.hpp"
#include "solution.hpp"


class quicksortP: public problem{

  private:
    std::vector<int> *v_;
    int min_;
    int max_;

  public:
    quicksortP(){}
    quicksortP(std::vector<int>* v, int min, int max);
    bool isMin(void);
    std::pair<problem*,problem*> decompose(void);
    void solve(solution* s);
    // void write(void);

};