#pragma once
#include <iostream>
#include "monomio.hpp"
#include <vector>

class polinomio {
  protected:
    int grado;
    int terminos;
    std::vector<monomio> p;
  
  public:
    polinomio();
    polinomio(int coef[], const int tam);
    polinomio(std::vector<monomio> &v);
    int get_size(void);
    monomio get_element(int i);
    polinomio mutiplicar(polinomio& x);
};

std::ostream& operator<<(std::ostream &sout, polinomio &p);