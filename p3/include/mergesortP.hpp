#pragma once
#include <iostream>
#include <vector>
#include "problem.hpp"
#include "solution.hpp"


class mergesortP: public problem{

  private:
    std::vector<int> v_;
    int ini_;
    int m_;
    int fin_;
    int n_;

  public:
    mergesortP(){}
    mergesortP(std::vector<int> v, int i, int f, int n);
    mergesortP(std::vector<int> v);
    bool isMin(void);
    std::pair<problem*,problem*> decompose(void);
    void solve(solution* s);
    std::vector<int> divide(int ini, int fin);
    void write(void);

    };