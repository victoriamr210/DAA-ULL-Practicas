#include <iostream>
#include "polinomio.hpp"
#include "monomio.hpp"
#include <vector>
#include <utility>

class algoritmo{
  public:
    virtual void multiplicar(polinomio &p, polinomio &q)=0;
};

class tradicional : public algoritmo{
  void multiplicar(polinomio &p, polinomio &q){
    int sum = 0;
    std::vector<monomio> v;
    int n = 0;
    if(p.get_size() <= q.get_size()){
      n = q.get_size();
    } else {
      n = p.get_size();
    }
    std::cout << "n: " << n << "\n";
    for(int i=0; i<=2*n-2; i++){
      // std::cout << "i: " << i << "\n";
      sum = 0;
      for(int j=0; j<=i; j++){
        if((i-j) < q.get_size() && j < p.get_size()){
        sum+=p.get_element(j).get_coef()*q.get_element(i-j).get_coef();
        } 
      }
      monomio aux(sum,i);
      v.push_back(aux);
    }
    polinomio pol(v);
    std::cout << "Resultaodo: " << pol ;
    // return pol;
  }
};

class DyV : public algoritmo{
  void multiplicar(polinomio &p, polinomio &q){
    polinomio resultado = multiplicar_r(p,q);
    std::cout << "\nResultado final: " << resultado;
  }

  polinomio multiplicar_r(polinomio &fp, polinomio &sp){
    if(fp.get_size() == 1 && sp.get_size() == 1){
      int coef = fp.get_element(0).get_coef() * sp.get_element(0).get_coef();
      int exp = fp.get_element(0).get_exp() + sp.get_element(0).get_exp();
      monomio aux(coef, exp);
      std::vector<monomio> v;
      v.push_back(aux);
      polinomio p(v);
      return p;
    } else {

      int n = fp.get_size();
      std::pair<polinomio, polinomio> fpd= dividir(fp);
      std::pair<polinomio, polinomio> spd = dividir(sp);

      // polinomio plow = fpd.first;
      // polinomio phigh = fpd.second;

      // polinomio qlow = spd.first;
      // polinomio qhigh = spd.second;

      // polinomio rl;
      // polinomio rm;
      // polinomio rh;
      polinomio rl = multiplicar_r(fpd.first, spd.first);
      polinomio rh = multiplicar_r(fpd.second, spd.second);
      polinomio aux1 = fpd.first + fpd.second;
      polinomio aux2 = spd.first + spd.second;
      polinomio rm = multiplicar_r(aux1, aux2);

      polinomio aux3 = rm - rl;
      polinomio aux4 = (aux3 - rh);
      polinomio aux5 = aux4 * (n/2);
      polinomio aux6 = rh * n;
      polinomio aux7 = rl + aux5;
      polinomio resul = aux7 + aux6;
      // polinomio resul = aux7 + (rh * n);

      return resul;

    }
  }



  std::pair<polinomio,polinomio> dividir(polinomio &p){

    int low = (p.get_size()/2);
    int high = p.get_size() - (p.get_size()/2);
    bool isOne = false;
    // std::cout << "size: " << p.get_size() << "\n";
    // std::cout << "Low: " << low << "\n";
    // std::cout << "high: " << high << "\n";

    std::pair<polinomio,polinomio> aux;
    std::vector<monomio> v1;
    std::vector<monomio> v2;

    
    for(int i = 0; i<low; i++){
      monomio aux(p.get_element(i).get_coef(), i);
      // monomio aux = p.get_element(i);
      v1.push_back(aux);
    }
     int iter = 0;
    for(int i = low; i<p.get_size(); i++){
      monomio aux(p.get_element(i).get_coef(), iter);
      // monomio aux = p.get_element(i);
      v2.push_back(aux);
      iter++;
    }

    polinomio p1(v1);
    polinomio p2(v2);

    aux.first = p1;
    aux.second = p2;
    return aux;
  }
};


class producto{
  protected:
    algoritmo *a_;
  
  public:
    producto(){
      a_=NULL;
    }

    producto(algoritmo *a){
      a_=a;
    }

    void set_a(algoritmo *a){
      a_=a;
    }

    void operar_m(polinomio &p, polinomio &q){
      if(a_){
        a_->multiplicar(p,q);
      }else{
        std::cout << "Error\n";
      }
    }
};