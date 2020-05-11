#pragma once
#include <iostream>
#include "solution.hpp"
#include "strategy.hpp"
#include "problem.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <limits>
#include <chrono>


class localSearch : public algorithm{
  Problem p_;
  int M = 3;

  void set_problem(Problem& p){
    p_ = p;
  }

  void solve(Problem& p){
    srand(time(NULL));
    set_problem(p);
    auto t1 = std::chrono::high_resolution_clock::now();
    Solution s = execute();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    s.set_time(duration);
    s.write();
  }

  std::vector<int> random_solution(void) {
    std::vector<int> s;
    for(int i = 0; i < M; i++){
      s.push_back(rand() % p_.get_elements());
    }
    return s;
  }

  Solution execute(void){
    std::vector<int> sol;
    float distance = get_total(sol);
    std::vector<int> bestSol = random_solution();
    while (bestSol == sol) {
      
    }

  }

  float get_total(std::vector<int> sol){
    float aux = 0;
    for(int i = 0; i < sol.size(); i++) {
      for(int j = i+1; j < sol.size(); j++) {
        aux += p_.get_distance(sol[i], sol[j]);
      }
    }
    return aux;
  }
};