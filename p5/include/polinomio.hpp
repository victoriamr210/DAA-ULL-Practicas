#pragma once
#include <iostream>
#include "monomio.hpp"
#include <vector>

class polinomio {
  protected:
    int grado;
    int terminos;
    std::vector<monomio> p;
    int* coef_;
  
  public:
    polinomio();
    polinomio(int coef[], const int tam);
    polinomio(std::vector<monomio> &v);
    int get_size(void);
    int get_grado(void);
    monomio get_element(int i);
    void set_element(monomio m, int);
    polinomio mutiplicar(polinomio& x);
    void write(void);
    void sumar(polinomio &pol);
};

std::ostream &operator<<(std::ostream &sout, polinomio &p);
polinomio operator+(polinomio &p, polinomio &q);
polinomio operator-(polinomio &p, polinomio &q);
polinomio operator*(polinomio &p, int cte);