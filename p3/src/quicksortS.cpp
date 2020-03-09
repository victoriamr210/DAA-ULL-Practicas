#include <iostream>
#include "../include/quicksortS.hpp"
#include "../include/quicksortP.hpp"

quicksortS::~quicksortS(){}

void quicksortS::solve_s(void){
  for(int i=0; i<(*v_).size(); i++){
    std::cout << (*v_).at(i) << " ";
  }
  std::cout << "\n";
}

void quicksortS::combine(std::pair<solution*,solution*> subS){
  v_ = ((quicksortS*)subS.first)->v_;
}

solution* quicksortS::getInstance(void){
  return new quicksortS();
}

void quicksortS::set(std::vector<int>* v){
  v_=v;
}