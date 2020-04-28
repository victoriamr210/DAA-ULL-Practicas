#pragma once
#include "graph.hpp"
#include <set>

/*Clase de que resuelve el problema segun un algoritmo*/
class algoritmo{
  public:
    virtual void solve(graph &g, bool greedy)=0;
};

/*Clase context para que permite ejecutar el algoritmo elegido*/
class resolve{
  protected:
  /*Algoritmo a ejecutar*/
    algoritmo *a_;
    bool greedy_;
  
  public:
  /*Constructor por defecto*/
    resolve(){
      a_=NULL;
    }
    /*Constructor de la clase*/
    resolve(algoritmo *a, bool greedy){
      a_=a;
      greedy_ = greedy;
    }
    /*Setter del algoritmo a ejecutar*/
    void set_a(algoritmo *a){
      a_=a;
    }
    /* Setter del booleano que indica si usar greedy o no*/
    void set_greedy (bool greedy) {
      greedy_ = greedy;
    }
    /*Funcion que llama al algoritmo correspondiente*/
    void get_solution(graph& g){
      if(a_){
        a_->solve(g, greedy_);
      }else{
        std::cout << "Error\n";
      }
    }
};