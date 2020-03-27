#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "../include/monomio.hpp"
#include "../include/polinomio.hpp"
#include "../include/estrategia.hpp"

void build_pol(std::vector<monomio> &v, int size){
  int coef = 0;
  for(int i=0; i<size+1; i++){
    coef = rand() % 11;
    // std::cout << coef << "\n";
    monomio m(coef, i);
    v.push_back(m);
  }
}


int main(int argc, char* argv[]) {
    // srand(time(NULL));
  srand(23);
  int size = atoi(argv[1]);

  std::vector<monomio> v;

  build_pol(v, size);
  polinomio p1(v);
  std::cout << "polinomio 1: " << p1;


  v.clear();
  
  build_pol(v,size);
  polinomio p2(v);
  std::cout << "Polinomio 2: "<< p2;

  producto *t;
  producto *dyv;

  polinomio re1;
  polinomio re2;

  t = new producto(new tradicional());
  auto t1 = std::chrono::high_resolution_clock::now();
  t->operar_m(p1, p2);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto total1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  std::cout << total1 << "ms Algoritmo tradicional\n";

  dyv = new producto(new DyV());
  auto t3 = std::chrono::high_resolution_clock::now();
  dyv->operar_m(p1, p2);
  auto t4 = std::chrono::high_resolution_clock::now();
  auto total2 = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();


  std::cout << total2 << "ms Algoritmo DyV\n";
}