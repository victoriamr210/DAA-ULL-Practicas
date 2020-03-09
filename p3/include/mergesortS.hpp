#pragma once
#include <iostream>
#include <vector>
#include "problem.hpp"

class mergesortS: public solution{
  private:
    std::vector<int> v_;
    // int* ve_;
    int ini_;
    int m_;
    int fin_;
    int n_;
    
  public:
    mergesortS(){}
    virtual ~mergesortS();

    void solve_s(void);
    void combine(std::pair<solution*,solution*> subsolutions);
    solution* getInstance(void);
    std::vector<int> getfull(std::pair<solution *, solution *> subS);
    int size(void);
    void set(std::vector<int> v); 

    void write(void);
    int get_ini(void);
    int get_fin(void);
    int get_n(void);
    std::vector<int> get_vector(void);
    void set_values(std::pair<solution *, solution *> subS);

    };