#pragma once
#include <iostream>
#include "strategy.hpp"
#include "problem.hpp"
#include "solution.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <chrono>

class voraz : public algorithm{
  public:
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

  Solution execute(void){
    std::vector<int> elem;
    for(int i = 0; i < p_.get_elements(); i++) {
      elem.push_back(i);
    }
    std::vector<int> s;
    std::vector<float> Sc = p_.center(elem);
    // float distance = 0;

    while (s.size() != M){
      int sStar = closest(Sc, elem);
      s.push_back(sStar);
      elem.erase(std::find(elem.begin(), elem.end(), sStar));
      Sc = p_.center(s);
    }
    float distance = get_total(s);
    return Solution(p_, s, distance);
  }


  int closest(std::vector<float> Sc, std::vector<int> elem) {
    float distance = 0;
    int sol;
    std::vector<int> repeat;

    for (int i = 0; i < elem.size(); i++){
      float aux = 0;
      for(int j = 0; j < p_.get_dimension(); j++){
        aux += pow(Sc[j] - p_.get_item(elem[i], j), 2);
      }

      aux = sqrt(aux);
      if (aux > distance) {
        distance = aux;
        sol = elem[i];
        repeat.clear();
        repeat.push_back(elem[i]);
      } else if (aux == distance) {
        repeat.push_back(elem[i]);
      }
    }

    if (repeat.size() > 1){
      int index = rand() % repeat.size();
      return repeat[index];
    }
    return sol;
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