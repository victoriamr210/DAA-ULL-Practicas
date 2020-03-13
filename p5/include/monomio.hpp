#pragma once
#include <iostream>

class monomio {
  private:
    int coeficiente;
    int exponente;

  public:
    monomio();
    monomio(int coef, int exp);
    int evaluar(int x) const;
    int get_coef(void) const;
    int get_exp(void) const;
    void set_coef(int c);
    void set_exp(int e);
};

std::ostream& operator<<(std::ostream &sout, const monomio &s);
std::istream& operator>>(std::istream &sin, monomio &r);

monomio operator+(const monomio &x, const monomio &y);
monomio operator*(const monomio &x, const monomio &y);