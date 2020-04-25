#pragma once
#include "graph.hpp"
#include <set>

/*Clase de que resuelve el problema segun un algoritmo*/
class algoritmo{
  public:
    virtual void solve(graph &g)=0;
};

/*Clase context para que permite ejecutar el algoritmo elegido*/
class resolve{
  protected:
  /*Algoritmo a ejecutar*/
    algoritmo *a_;
  
  public:
  /*Constructor por defecto*/
    resolve(){
      a_=NULL;
    }
    /*Constructor de la clase*/
    resolve(algoritmo *a){
      a_=a;
    }
    /*Setter del algoritmo a ejecutar*/
    void set_a(algoritmo *a){
      a_=a;
    }
    /*Funcion que llama al agoritmo correspondiente*/
    void get_solution(graph& g){
      if(a_){
        a_->solve(g);
      }else{
        std::cout << "Error\n";
      }
    }
};