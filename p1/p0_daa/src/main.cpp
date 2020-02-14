#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include "../include/matrix.hpp"
#include "../include/strategy.hpp"



int main(void){

  Context *pc;
  Context *pc1;
  Context *pc2;
  // int a[N][M];
  // int b[M][X];
  // int c[30][30];
  Matrix a(500,500, 78);
  Matrix b(500,500,19);
  // Matrix c(500,500);


  // std::cout << "Matriz A:\n";
  // a.write();
  // a.trasponer();
  // a.write_t();
  // std::cout << "Matriz B:\n";
  // b.write();
  

  pc= new Context(new StrategyRow());
  auto t1 = std::chrono::high_resolution_clock::now();
  pc->ContextInterface(a,b);
  auto t2 = std::chrono::high_resolution_clock::now();

  pc1 = new Context(new StrategyCol());
  auto t3 = std::chrono::high_resolution_clock::now();
  pc1->ContextInterface(a, b);
  auto t4 = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  std::cout << duration << " milisegundos por filas\n";

  auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
  std::cout << duration1 << " milisegundos por columnas\n";
  
  b.trasponer();
  pc2=new Context(new StrategyTras());
  auto t5 = std::chrono::high_resolution_clock::now();
  pc2->ContextInterface(a,b);
  auto t6 = std::chrono::high_resolution_clock::now();

  auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count();
  std::cout << duration2 << " milisegundos por traspuesta\n";
}

