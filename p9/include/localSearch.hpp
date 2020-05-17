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


class localSearch : public algorithm{
  Problem p_;
  int M;
  public:
  // voraz greedy;
  Solution initial; 
  localSearch(int m, Solution i) {
    M = m;
    initial = i;
    // greedy.set_m(m);
  }

  void set_problem(Problem& p){
    p_ = p;
  }

  Solution solve(Problem& p){
    srand(time(NULL));
    set_problem(p);
    auto t1 = std::chrono::high_resolution_clock::now();
    // greedy.set_problem(p);
    // Solution aux = greedy.execute();
    std::vector<int> sol = initial.get_vector();
    Solution s = execute(sol);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    s.set_time(duration);
    s.write();
    return s;
  }

  std::vector<int> random_solution(void) {
    std::vector<int> s;
    for(int i = 0; i < M; i++){
      s.push_back(rand() % p_.get_elements());
    }
    return s;
  }

  Solution execute(std::vector<int> sol){
    std::vector<int> solution = sol;
    float distance = get_total(sol);
    bool change = true;
    while (change) {
      std::vector<int> aux = local_search(solution);
      if (get_total(aux) > distance) {
        solution = aux;
        distance = get_total(aux);
      } else {
        change = false;
      }
    }
    return Solution (p_, solution, distance);

  }

  std::vector<int> local_search(std::vector<int> sol){
    float distance = get_total(sol);
    std::vector<int> optimum;
    std::vector<int> aux = sol;
    bool change = false;
    do {
      std::vector<int> cand = get_candidates(aux);
      change = false;
      for(int i = 0; i < aux.size(); i++){
        int auxItem = aux[i];
        for (int j = 0; j < cand.size(); j++){
          aux[i] = cand[j];
          float auxDistance = get_total(aux);
          if (auxDistance > distance) {
            distance = auxDistance;
            optimum = aux;
            change = true;
          }
        }
        aux[i] = auxItem;
      }
    } while (change);
    return optimum;
  }

  std::vector<int> get_candidates(std::vector<int> sol){
    std::vector<int> cand;
    for(int i = 0; i < p_.get_elements(); i++){
        cand.push_back(i);
    }
    for(int i = 0; i < sol.size(); i++){
      cand.erase(std::find(cand.begin(), cand.end(), sol[i]));
    }
    return cand;
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