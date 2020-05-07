#pragma once
#include <iostream>
#include "strategy.hpp"
#include "problem.hpp"
#include "solution.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <limits>
#include <chrono>

class newVoraz : public algorithm{
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
    std::vector<int> s = elem;
    std::vector<float> Sc = p_.center(elem);
    float distance = 0;

    while (s.size() != M){
      int sStar = furthest(Sc, elem);
      s.erase(std::find(s.begin(), s.end(), sStar));
      elem.erase(std::find(elem.begin(), elem.end(), sStar));
      Sc = p_.center(s);
    }
    return Solution(p_, s);
  }


  int furthest(std::vector<float> Sc, std::vector<int> elem) {
    // std::cout << "\n\nfurthset" << elem.size() << "\n";
    std::numeric_limits<int>::min();
    float distance = std::numeric_limits<float>::max();
    int sol;
    std::vector<int> repeat;

    for (int i = 0; i < elem.size(); i++){
      float aux = 0;
      // std::cout << "Resta: " << i << "\n";
      for(int j = 0; j < p_.get_dimension(); j++){
        // std::cout << Sc[j] << " - " << p_.get_item(elem[i], j) << "^2 ="
        //           << pow(Sc[j] - p_.get_item(elem[i], j), 2)  << "\n";
        aux += pow(Sc[j] - p_.get_item(elem[i], j), 2);
      }

      aux = sqrt(aux);
      // std::cout << "aux:" << aux << " dis:" << distance << "\n";
      if (aux < distance) {
        distance = aux;
        sol = elem[i];
        repeat.clear();
        repeat.push_back(elem[i]);
      } else if (aux == distance) {
        repeat.push_back(elem[i]);
      }
    }
    // std::cout << "\nSol: " << sol << "\n";

    if (repeat.size() > 1){
      int index = rand() % repeat.size();
      return repeat[index];
    }
    return sol;
  }
};