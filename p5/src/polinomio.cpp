#include "../include/polinomio.hpp"

polinomio::polinomio(){}

polinomio::polinomio(int coef[], const int tam){

}

polinomio::polinomio(std::vector<monomio> &v){
  p = v;
  terminos = p.size();
}

int polinomio::get_size(void){
  return p.size();
}

monomio polinomio::get_element(int i){
  return p[i];
}

std::ostream &operator<<(std::ostream &sout, polinomio &p){
  for(int i=0; i<p.get_size(); i++){
    if(p.get_element(i).get_coef() != 0){
    sout << p.get_element(i) << " ";
    }
  }
  sout << "\n";
}



