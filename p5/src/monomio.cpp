#include "../include/monomio.hpp"
#include <math.h>

monomio::monomio(){}

monomio::monomio(int coef, int exp){
  coeficiente = coef;
  exponente = exp;
}

int monomio::evaluar(int x) const{
  return coeficiente * pow(x, exponente);
}

int monomio::get_coef(void) const{
  return coeficiente;
}

int monomio::get_exp(void) const{
  return exponente;
}

void monomio::set_coef(int c){
  coeficiente = c;
}

void monomio::set_exp(int e){
  exponente = e;
}

std::ostream &operator<<(std::ostream &sout, const monomio &s){
  sout << s.get_coef() << "x^" << s.get_exp();
  return sout;
}


std::istream &operator>>(std::istream &sin, monomio &r){
  int coef, exp;
  sin >> coef >> exp;
  r.set_coef(coef);
  r.set_exp(exp); 
  return sin;
}

monomio operator+(const monomio &x, const monomio &y){
  if(x.get_exp() == y.get_exp()){
    int coef = x.get_coef() + y.get_coef();
    monomio m(coef, y.get_exp());
    return m;
  } else {
    std::string e = "No se puede sumar, distintos exponentes\n";
    throw e;
  }
}

monomio operator*(const monomio &x, const monomio &y){
  int coef = x.get_coef() * y.get_coef();
  int exp = x.get_exp() + y.get_exp();
  monomio m(coef, exp);
  return m;
}

