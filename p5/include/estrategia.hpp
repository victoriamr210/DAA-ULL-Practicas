#include <iostream>
#include "polinomio.hpp"

class algoritmo{
  public:
    virtual void multiplicar(polinomio &a, polinomio &b)=0;
};

class tradicional : public algoritmo{
  void multiplicar(polinomio &a, polinomio &b){
    
  }
};


class producto{
  protected:
    algoritmo *a_;
  
  public:
    producto(){
      a_=NULL;
    }

    producto(algoritmo *a){
      a_=a;
    }

    void set_a(algoritmo *a){
      a_=a;
    }

    void operar_m(polinomio &a, polinomio &b){
      if(a_){
        a_->multiplicar(a,b);
      }else{
        std::cout << "Error\n";
      }
    }
};