#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

class Matrix{
  private:
    int n_;
    int m_;
    std::vector<int> v_;

  public:
    Matrix(int n, int m, int seed){
      n_=n;
      m_=m;
      v_.resize(n_*m_);
      srand(seed);
      set();
    }

    Matrix(int n, int m){
      n_=n;
      m_=m;
      v_.resize(n_*m_);
    }

    int pos(int i, int j){
      return v_[i*(n_)+j];
    }

    int pos_i(int i, int j){
      return i*(n_)+j;
    }

    void set_item(int i, int j, int val){
      v_[pos_i(i,j)]+=val;
    }

    void set_i(int i, int j, int val){
      v_[pos_i(i,j)]=val;
    }
    
    void set(void){
      for(int i=0; i<n_*m_; i++){
        v_[i]=rand() % 9;

      }
    }

    void write(void){
      for(int i=0; i<n_; i++){
        for(int j=0; j<m_; j++){
          std::cout << pos(i,j) << " ";
        }
        std::cout << "\n";
      }
      std::cout << "\n";
    }

    int get_n(void){ return n_;}
    
    int get_m(void){return m_;}

};

class Strategy{
  public:
   virtual void multiply(Matrix &a, Matrix &b)=0;
};


class StrategyRow : public Strategy{
  void multiply(Matrix &a, Matrix &b){
    // std::cout << "row\n";
    if(a.get_m()==b.get_n()){
      int val=0;
      Matrix aux(a.get_n(), b.get_m());
      for(int i=0; i<a.get_n(); i++){
        for(int j=0; j<b.get_m(); j++){
          for(int k=0; k<a.get_m(); k++){
            // aux.set_item(i,j,a.pos(i,k) * b.pos(k,j));
            val += a.pos(i,k) * b.pos(k,j);
            // std::cout << a.pos(i, k) << " * " << b.pos(k, j) << " = " << a.pos(i, k) * b.pos(k, j) << "\n";
          }
          // std::cout << "m[" << i << "][" << j << "] = " << val << "\n";
          aux.set_i(i,j,val);
          val=0;
        }
      }

    }else{
      std::cout << "No se puede hacer el producto\n";
    }
  }
};

class StrategyCol : public Strategy{ 
  void multiply(Matrix &a, Matrix &b){
    if(a.get_m()==b.get_n()){
      int val=0;
      Matrix aux(a.get_n(), b.get_m());
      for(int i=0; i<a.get_n(); i++){
        for(int j=0; j<b.get_m(); j++){
          for(int k=0; k<a.get_m(); k++){
            // std::cout << "i: " << i << " j:" << j << " k; " << k << "\n";
            // aux.set_item(j,i,a.pos(i,k) * b.pos(k,j));
            val += a.pos(i,k) * b.pos(k,j);
            // std::cout << val << std::endl;
          }
          aux.set_i(j,i,val);
          val=0;
        }
      }

    }else{
      std::cout << "No se puede hacer el producto\n";
    }
  }
};

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

int main(void){

  Context *pc;
  Context *pc1;
  Matrix a(4,4,10);
  Matrix b(4,4,5);

  // std::cout << "Matriz A:\n";
  // a.write();
  // std::cout << "Matriz B:\n";
  // b.write();

 

  pc1 = new Context(new StrategyCol());
  auto t3 = std::chrono::high_resolution_clock::now();
  pc1->ContextInterface(a, b);
  auto t4 = std::chrono::high_resolution_clock::now();

  pc = new Context(new StrategyRow());
  auto t1 = std::chrono::high_resolution_clock::now();
  pc->ContextInterface(a, b);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << duration << " microsegundos por filas\n";

  auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
  std::cout << duration1 << " microsegundos por columnas\n";
}

