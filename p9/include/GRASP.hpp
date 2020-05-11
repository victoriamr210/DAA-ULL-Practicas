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

class GRASP : public algorithm{
  Problem p_;
  int M = 3;
  const int RCL_size = 3;
  const int ITERATIONS = 10;

  void set_problem(Problem& p){
    p_ = p;
  }

  int select_random(std::vector<int> v){
    if (v.size() > 1) {
      int index = rand() % v.size();
      return v[index];
    }
    return v[0];
  }

  void solve(Problem &p) {
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

  Solution execute(void) {
    float distance = std::numeric_limits<float>::min();
    int cont = 0;
    std::vector<int> bestSol;
    std::vector<int> sol;
    while (cont != ITERATIONS) {
      std::vector<int> sol = constructor();
      sol = local_search(sol);
      float auxDistance = get_total(sol);
      if (auxDistance > distance) {
        bestSol = sol;
        distance = auxDistance;
        cont = 0;
      } 
      else {
        cont++;
      }
    }
    return Solution(p_, bestSol, distance);
  }

  std::vector<int> constructor(){
    int n = p_.get_elements();
    int k = rand() %  (n - 2) + 2;
    std::vector<int> sol;
    sol.push_back(rand() % n);
    while(sol.size() < M) {
      std::vector<int> rcl = buildRCL(sol);
      int element = select_random(rcl);
      sol.push_back(element);

    }
    // for (int i = 0; i < M -1; i++){
    // }
    return sol;
  }

  std::vector<int> buildRCL(std::vector<int> sol) {
    std::vector<int> cand = get_candidates(sol);
    std::vector<int> vectors;
    std::vector<float> dis;
    for(int i = 0; i < cand.size(); i++) {
      sol.push_back(cand[i]);
      float distance = get_total(sol);
      sol.pop_back();

      int pos = 0;
      for (int j = 0; j < dis.size(); j++) {
        if (distance < dis[j]){
          pos++;
        }
      }
      dis.insert(dis.begin() + pos, distance);
      vectors.insert(vectors.begin() + pos, cand[i]);
    }

    std::vector<int> aux;
    for(int i = 0; i < RCL_size; i++){
      aux.push_back(vectors[i]);
    }

    return aux;
  }

  // std::vector<int> local_search(std::vector<int> sol){
  //   bool flag = true;
  //   while (flag) {
  //     flag = false;
  //     std::vector<int> aux = exchange(sol);
  //     if (aux != sol){
  //       flag = true;
  //     }
  //   }
  //   return sol;
  // }

  std::vector<int> local_search(std::vector<int> sol){
    std::vector<int> cand = get_candidates(sol);
    float distance = get_total(sol);
    std::vector<int> optimum = sol;
    for(int i = 0; i < sol.size(); i++){
      int auxItem = sol[i];
      for (int j = 0; j < cand.size(); j++){
        sol[i] = cand[j];
        float auxDistance = get_total(sol);
        if (auxDistance > distance) {
          distance = auxDistance;
          optimum = sol;
        }
      }
      sol[i] = auxItem;
    }
    return optimum;
  }

  float get_total(std::vector<int> sol) {
    float aux = 0;
    for(int i = 0; i < sol.size(); i++) {
      for(int j = i+1; j < sol.size(); j++) {
        aux += p_.get_distance(sol[i], sol[j]);
      }
    }
    return aux;
  }
};