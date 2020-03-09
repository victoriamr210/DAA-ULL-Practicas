#include "../include/mergesortP.hpp"
#include "../include/mergesortS.hpp"

mergesortP::mergesortP(std::vector<int> v, int i, int f, int n){
  v_=v;
  ini_=i;
  fin_=f;
  m_=(i+f)/2;
  n_=n;
  // std::cout << "i: " << ini_ << " m: " << m_ << " f:" << fin_ << "\n";

}

mergesortP::mergesortP(std::vector<int> v){
  v_=v;
  // std::cout << "i: " << ini_ << " m: " << m_ << " f:" << fin_ << "\n";

}

bool mergesortP::isMin(void){
  return (v_.size() < 2);
  // return ini_ >= fin_;
}

std::pair<problem *, problem *> mergesortP::decompose(void){
  // std::cout << "dcompose ";
  std::pair<problem*,problem*> subP;
  std::vector<int> aux;

    std::cout << v_.size() / 2 << "\n";

  for(int i=0; i<(v_.size() / 2); i++){
    aux.push_back(v_[i]);
  }
  // std::cout << "fisrt\n ";

  // for(int i=0; i<aux.size(); i++){
  //   std::cout << aux[i] << " ";
  // }
  // std::cout << "\n";
  subP.first = new mergesortP(aux);
  aux.clear();
  // std::cout << "second\n ";
  for(int i=(v_.size() / 2); i<v_.size(); i++){
    aux.push_back(v_[i]);
  }
  // std::cout << "\n";

  // for(int i=0; i<aux.size(); i++){
  //   std::cout << aux[i] << " ";
  // }
  // std::cout << "\n";
  subP.second = new mergesortP(aux);
  return subP;
}

void mergesortP::solve(solution* s){
  // std::cout << "solve ";
  // ((mergesortS*)s)->set(v_,ini_,fin_,n_);
  ((mergesortS*)s)->set(v_);

  // ((mergesortS*)s)->set(v_,ini_,fin_);

}

std::vector<int> mergesortP::divide(int ini, int fin){
  std::vector<int> aux(fin -ini);
  int k=0;
  for(int i=ini; i<=fin; i++){
    aux[k] = v_[i];
    k++;
  }
}

void mergesortP::write(void){
  for(int i=ini_; i<=fin_; i++){
    std::cout << v_[i] << " ";
  }
  std::cout << "\n";
}