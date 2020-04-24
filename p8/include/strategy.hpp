#pragma once
#include "graph.hpp"
#include <set>

class algoritmo{
  public:
    virtual void solve(graph &g)=0;
};


class new_voraz : public algoritmo{
  void solve(graph &g);
};

class GRASP : public algoritmo{
  void solve(graph &g);
};

class multiarranque : public algoritmo{
  void solve(graph &g);
};

class busqueda_entorno : public algoritmo{
  void solve(graph &g);
};


class resolve{
  protected:
    algoritmo *a_;
  
  public:
    resolve(){
      a_=NULL;
    }

    resolve(algoritmo *a){
      a_=a;
    }

    void set_a(algoritmo *a){
      a_=a;
    }

    void get_solution(graph& g){
      if(a_){
        a_->solve(g);
      }else{
        std::cout << "Error\n";
      }
    }
};