#include "../include/mergesortS.hpp"
#include "../include/mergesortP.hpp"

mergesortS::~mergesortS(){}

void mergesortS::solve_s(void){

    for(int i=0; i<v_.size(); i++){
      std::cout << v_[i] << " ";
    }
    std::cout << "\n";

}

void mergesortS::combine(std::pair<solution *, solution *> subS){

  std::vector<int> aux1 = ((mergesortS *)subS.first)->v_;
  std::vector<int> aux2 = ((mergesortS *)subS.second)->v_;

  int i = 0;
  int j = 0;
  int k = 0;

  v_.resize(aux1.size() + aux2.size());
  // std::cout << v_.size() << "\n";

  while(i < aux1.size() && j < aux2.size()){
    if(aux1[i] <= aux2[j]){
      v_[k] = aux1[i];
      // std::cout << aux1[i] << " <= " << aux2[j] << "\n";
      i++;
    } else {
      v_[k] = aux2[j];
      // std::cout << aux1[i] << " > " << aux2[j] << "\n";
      j++;
    }
    k++;
  }


  while(i < aux1.size()){
    v_[k] = aux1[i];
    i++;
    k++;
  }

  while(j < aux2.size()){
    v_[k] = aux2[j];
    j++;
    k++;
  }

 
}


void mergesortS::set_values(std::pair<solution *, solution *> subS){
  std::cout << "set_values ";
  int ini1 = ((mergesortS *)subS.first)->get_ini();
  int fin1 = ((mergesortS *)subS.first)->get_fin();
  int n = ((mergesortS *)subS.first)->size();
  std::vector<int> aux1 = ((mergesortS *)subS.first)->get_vector();
  int ini2 = ((mergesortS *)subS.second)->get_ini();
  int fin2 = ((mergesortS *)subS.second)->get_fin();
  std::vector<int> aux2 = ((mergesortS *)subS.second)->get_vector();

  v_.resize(fin2 - ini1);
  std::cout << "ini1:" << ini1 << " fin1:" << fin1;
  std::cout << " ini2:" << ini2 << " fin2:" << fin2 << "\n";
  std::cout << " n:" << n << "\n";

}

solution* mergesortS::getInstance(void){
  return new mergesortS();
}

std::vector<int> mergesortS::getfull(std::pair<solution *, solution *> subS){
  int a = ((mergesortS*)subS.first)->size() + ((mergesortS*)subS.second)->size();
  std::vector<int> v(a);
  std::vector<int> aux(a);


}

std::vector<int> mergesortS::get_vector(void){
  return v_;
}

int mergesortS::get_ini(void){
  return ini_;
}

int mergesortS::get_n(void){
  return n_;
}

int mergesortS::get_fin(void){
  return fin_;
}

int mergesortS::size(void){
  return v_.size();
}

void mergesortS::set(std::vector<int> v){
  v_ = v;
}

void mergesortS::write(void){
  std::cout << "Swrite ";
  for (int i = 0; i <= v_.size(); i++){
    std::cout << v_[i] << " ";
  }
  std::cout << "\n";
}