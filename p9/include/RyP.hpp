#pragma once
#include <iostream>
#include "solution.hpp"
#include "strategy.hpp"
#include "problem.hpp"
#include "node.hpp"
#include <vector>
#include <math.h>
#include <algorithm>
#include <time.h>
#include <limits>
#include <chrono>


class RyP : public algorithm {
  Problem p_;
  int M;
  Solution inferior;
  float lower_bound;
  std::vector<std::vector<Node>> tree_;
  std::vector<Node> tree2_;
  std::vector<int> activeNodes;
  std::vector<int> currentSol;
  bool minCota;
  int currentK;

  public:

  RyP(int m, Solution i, bool min){
    M = m;
    inferior = i;
    lower_bound = inferior.get_value();
    minCota = min;
  }

  void set_problem(Problem& p){
    p_ = p;
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

  Solution solve(Problem& p){

    set_problem(p);
    auto t1 = std::chrono::high_resolution_clock::now();
    Solution s = execute();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    s.set_time(duration);
    s.write();
    return s;

  }

  Solution execute(){
    // std::cout << "lower " << lower_bound << "\n";

    initialize_tree();
    currentK++;
    // write2();
    while(activeNodes.size() != 0){

      // std::cout << "1 " << activeNodes.size() << "\n";
      prune();
      // std::cout << "2 " << activeNodes.size() << "\n";
      int pos = get_minimum();

      // std::cout << "3 " << activeNodes.size() << "\n";
      if(pos != -1){
        expand(pos);
        check_for_sol();
      }else{
        // std::cout << "5 " << activeNodes.size() << "\n";

        break;

      }
    }
    float dis = get_total(currentSol);
    // Solution s(p_, currentSol, dis);
    // s.write();
    return Solution(p_, currentSol, dis);
  }

  void initialize_tree(void){
    int n = p_.get_elements();
    for(int i = 0; i < (n-(M-1)); i++){
      std::vector<int> s;
      s.push_back(i);
      float upb = calculate_UB(s);
      Node aux(0, upb);
      aux.set_sol(s);
      tree2_.push_back(aux);
      activeNodes.push_back(tree2_.size() - 1);
    }
  }

  float calculate_UB(std::vector<int> s){

    // std::cout << "upper\n";
    std::vector<int> unSel = get_candidates(s);
    std::vector<float> upperB2;
    std::vector<float> upperB3;
    for(int i = 0; i < s.size(); i++){
      for(int j = 0; j < unSel.size(); j++){
        float distance = p_.get_distance(s[i], unSel[j]);
        int pos = 0;
        for (int k = 0; k < upperB2.size(); k++) {
          if (distance < upperB2[k]){
          pos++;
          }
        }
        upperB2.insert(upperB2.begin() + pos, distance);
      }
    }
    int k = s.size();
    // if(k == 1){

    // for(int i = 0; i< upperB2.size(); i++){
    //   std::cout << upperB2[i] << " ";
    // }
    // std::cout << "\n";
    // }
    int size = k * (M - k);
    float UB2=0;
    for(int i = 0; i < size; i++){
      UB2 += upperB2[i];
    }



    
    for (int i = 0; i < unSel.size(); i++){
      for (int j = i+1; j < unSel.size(); j++){
        float distance = p_.get_distance(unSel[i], unSel[j]);

        int pos = 0;
        for (int k = 0; k < upperB3.size(); k++) {
          if (distance < upperB3[k]){
            pos++;
          }
        }
        upperB3.insert(upperB3.begin() + pos, distance);
      }
    }
    // if(k == 1){

    // for(int i = 0; i< upperB3.size(); i++){
    //   std::cout << upperB3[i] << " ";
    // }
    // std::cout << "\n--------------------------\n";
    // }
    size = 0;
    for (int i = M - k - 1; i > 0; i--) {
      size += i;
    }
    // size -= 1;
    float UB3=0;
    for(int i = 0; i < size; i++){
      UB3 += upperB3[i];
    }
    // std::cout << "UB3: " << UB3 << 
    // std::cout << UB2 + UB3 << "\n";
    return UB2 + UB3;
  }

  int get_minimum(void) {
    int pos = -1;
    if(minCota){

    float min = std::numeric_limits<float>::max();
    for(int i = 0; i < tree2_.size(); i++){
      // std::cout << tree2_[i].get_pruned() << tree2_[i].get_expanded() << tree2_[i].get_solution() << "\n";
      if(!tree2_[i].get_pruned() && !tree2_[i].get_expanded() && !tree2_[i].get_solution()){
        // std::cout << "min\n";
        float auxDis = tree2_[i].get_UB();
        if ((auxDis < min)) {
          min = auxDis;
          pos = i;
        }
      }
    }
    // return pos;
    }else {
      int deepK = -1;
      for(int i = 0; i < tree2_.size(); i++){
        if (!tree2_[i].get_pruned() && !tree2_[i].get_expanded() && !tree2_[i].get_solution()){
          int size = tree2_[i].get_sol().size();
          if (size > deepK){
            deepK = size;
            pos = i;
          }
        }
      } 
    }

    return pos;
  }

  void expand(int pos){
    tree2_[pos].set_expanded(true);
    // if (std::find(activeNodes.begin(), activeNodes.end(), pos) != activeNodes.end()){
      activeNodes.erase(std::find(activeNodes.begin(), activeNodes.end(), pos));
    // }
      int currentK = tree2_[pos].get_sol().size();
      int initial = tree2_[pos].get_sol().back() + 1;
      std::vector<int> partialSol = tree2_[pos].get_sol();
      int n = p_.get_elements();
    
      for (int i = initial; i < (n-(M-currentK)); i++){
        std::vector<int> s = partialSol;
        s.push_back(i);
        // std::cout << s.size() << " juan\n";
        // std::cout << "expand1\n";
        float upb = calculate_UB(s);
        // std::cout << "expand2\n";
        float value = get_total(s);
        Node aux(value, upb);
        aux.set_sol(s);
        tree2_.push_back(aux);
        activeNodes.push_back(tree2_.size() - 1);
      }
  }

  void prune(void) {
    for(int i = 0; i < tree2_.size(); i++){
      float up = tree2_[i].get_value() + tree2_[i].get_UB();
      if (up < lower_bound) {
        tree2_[i].set_pruned(true);
        if (std::find(activeNodes.begin(), activeNodes.end(), i) != activeNodes.end()){
          activeNodes.erase(std::find(activeNodes.begin(), activeNodes.end(), i));
        }
      }
    }
  }

  void check_for_sol(void){
    for(int i = 0; i < tree2_.size(); i++){
      if(tree2_[i].get_sol().size() == M) {
        tree2_[i].set_solution(true);
        // std::cout << "hola\n";
        std::vector<int> s  = tree2_[i].get_sol();
        if(get_total(s) >= lower_bound) {
          lower_bound = get_total(s);
          currentSol = s;
        }
      }
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
  
  void write(void){
    for(int i = 0; i < tree_.size(); i++){
      // std::cout << "profundidad: " << i+1 << "\n";
      for(int j = 0; j < tree_[i].size(); j++){
        tree_[i][j].write();
      }
    }
  }

  void write2(void){
    for(int i = 0; i < tree2_.size(); i++){
      tree2_[i].write();
    }
  }
  
};