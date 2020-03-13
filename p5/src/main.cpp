#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../include/monomio.hpp"
#include "../include/polinomio.hpp"
#include "../include/estrategia.hpp"

void build_pol(std::vector<monomio> &v, int size){
  int coef = 0;
  for(int i=0; i<size+1; i++){
    coef = rand() % 11;
    monomio m(coef, i);
    v.push_back(m);
  }
}


int main(int argc, char* argv[]) {
  try{
    srand(time(NULL));
    int size = atoi(argv[1]);

    std::vector<monomio> v;
    
    build_pol(v, size);
    polinomio p1(v);
    std::cout << p1;

    v.clear();
    build_pol(v,size);
    polinomio p2(v);
    std::cout << p2;

    producto *t;
    producto *dyv;

    t = new producto(new tradicional());
    t->operar_m(p1, p2);





  } catch(std::string e){
    std::cout << e;
  }
}