#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>

#define N 3
#define M 3
#define X 4


void set(int n, int m, int seed){
  srand(seed);
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
    // a[i][j]=rand() % 10;
    }

  }
}

class Strategy{
  public:
   virtual void multiply(int **a, int **b)=0;
};


class StrategyRow : public Strategy{
  void multiply(int **a, int **b){
    // std::cout << "row\n";
    // if(a.get_m()==b.get_n()){
      int val=0;
      int c[N][X];
      // Matrix aux(a.get_n(), b.get_m());
      for(int i=0; i<N; i++){
        for(int j=0; j<X; j++){
          for(int k=0; k<M; k++){
            c[i][j]+=a[i][k]*b[k][j];
            // val += a.pos(i,k) * b.pos(k,j);
            // std::cout << val << std::endl;
          }
          // aux.set_i(i,j,val);
          // val=0;
        }
      }
      // aux.write();

    // }else{
    //   std::cout << "No se puede hacer el producto\n";
    // }
  }
};

class StrategyCol : public Strategy{
  void multiply(int **a, int **b){
    // if(a.get_m()==b.get_n()){
      int val=0;
      int d[N][X];
      for(int i=0; i<N; i++){
        for(int j=0; j<X; j++){
          for(int k=0; k<M; k++){
            d[i][j]+=a[i][k]*b[k][j];
            // val += a.pos(i,k) * b.pos(k,j);
            // std::cout << val << std::endl;
          }
          // aux.set_i(i,j,val);
          // val=0;
        }
      }
    //   // aux.write();

    // }else{
    //   std::cout << "No se puede hacer el producto\n";
    // }
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

    void ContextInterface(int **a, int **b){
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
  
  int **a;
  int **b;



  srand(29);
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
    a[i][j]=rand() % 10;
    }
  }

  srand(22);
  for(int i=0; i<M; i++){
    for(int j=0; j<X; j++){
    b[i][j]=rand() % 10;
    }
  }


  // std::cout << "Matriz A:\n";
  // a.write();
  // std::cout << "Matriz B:\n";
  // b.write();

  pc= new Context(new StrategyRow());
  auto t1 = std::chrono::high_resolution_clock::now();
  // pc->ContextInterface(a,b);
  auto t2 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  std::cout << duration << " microsegundos por filas\n";

  pc1 = new Context(new StrategyCol());
  auto t3 = std::chrono::high_resolution_clock::now();
  pc1->ContextInterface(a, b);
  auto t4 = std::chrono::high_resolution_clock::now();

  auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
  std::cout << duration1 << " microsegundos por columnas\n";
}

