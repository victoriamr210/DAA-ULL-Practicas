#pragma once
#include <iostream>
#include "problem.hpp"

class algorithm {
  public:
    virtual void solve(Problem& p)=0;
};

class resolve {
  protected:
    algorithm* a_;
    
  public:
    resolve(){
      a_=NULL;
    }
    
    resolve(algorithm *a){
      a_=a;
    }

    void set_a(algorithm* a){
      a_=a;
    }

    void get_solution(Problem& p){
      if(a_){
        a_->solve(p);
      } else {
        std::cout << "Error\n";
      }
    }

};