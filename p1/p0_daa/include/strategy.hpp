#pragma once
#include <iostream>

//clase abstracta de estrategia
class Strategy{
  public:
   virtual void multiply(Matrix &a, Matrix &b)=0;
};

//clase de la estrategia por columnas
class StrategyRow : public Strategy{
  void multiply(Matrix &a, Matrix &b){
    // std::cout << "row\n";
    if(a.get_m()==b.get_n()){
      int val=0;
      Matrix c(a.get_n(), b.get_m());
      for(int i=0; i<a.get_n(); i++){
        for(int j=0; j<b.get_m(); j++){
          for(int k=0; k<a.get_m(); k++){
            val +=a.pos(i,k)*b.pos(k,j);
            // c[i][j]+=a.pos(i,k)*b.pos(k,j);
          }
          c.set_item(i,j, val);
          val=0;
        }
      }
      // c.write();

    }else{
      std::cout << "No se puede hacer el producto\n";
    }
  }
};

//clase de estrategia por columnas
class StrategyCol : public Strategy{
  void multiply(Matrix &a, Matrix &b){
    if(a.get_m()==b.get_n()){
      int val=0;
      Matrix c(a.get_n(), b.get_m());
      for(int i=0; i<b.get_m(); i++){
        for(int j=0; j<a.get_n(); j++){
          for(int k=0; k<a.get_m(); k++){
            val +=a.pos(j,k)*b.pos(k,i);

          }
          c.set_item(j,i, val);
          val=0;
        }
      }
      // c.write();

    }else{
      std::cout << "No se puede hacer el producto\n";
    }
  }
};


class StrategyTras : public Strategy{
  void multiply(Matrix &a, Matrix &b){

    if(a.get_m()==b.get_n()){
      int val=0;
      Matrix c(a.get_n(),b.get_m());
      for(int i=0; i<a.get_n(); i++){
        for(int j=0; j<b.get_m(); j++){
          for(int k=0; k<a.get_m(); k++){
            val +=a.pos(i,k)*b.pos_t(j,k);
          }
          c.set_item(i,j,val);
          val=0;
        }
      }
      // c.write();

    }else{
      std::cout << "No se puede hacer el producto\n";
    }
  }
};

//clase contexto
class Context{
  protected:
    Strategy *s_;
  
  public:
    Context(){
      s_=NULL;
    }

    Context(Strategy *s){
      s_=s;
    }

    void setSt(Strategy *s){
      s_=s;
    }

    void ContextInterface(Matrix &a, Matrix &b){
      if(s_){
        s_->multiply(a,b);
      }else{
        std::cout << "Error\n";
      }
    }

};