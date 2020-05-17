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
#include "node.hpp"

class Tree {
  private:
    std::vector<std::vector<Node>> t_;
    int depth_;

  public:
    Tree(int k){
      depth_ = k;
      t_.resize(k);
    }

    Node get_node(int d, int number) {
      return t_[d][number];
    }

    void set_node(int d, int number, Node node) {
       t_[d].push_back(node);
    }

    void erase_brach(int d, int number) {
      t_[d][number].set_pruned(true);
      if(((d + 1) < depth_) && !t_[d+1].empty()) {
        for(int i = 0; i < t_[d+1].size(); i++){
          t_[d+1][i].set_pruned(true);
        }
      }
    }


};