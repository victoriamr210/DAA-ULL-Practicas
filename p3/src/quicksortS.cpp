#include <iostream>
#include "../include/quicksortS.hpp"
#include "../include/quicksortP.hpp"

quicksortS::~quicksortS(){}

void quicksortS::solve_s(void){



  bool ordered = true;
    for(int i=1; i<(*v_).size(); i++){
      // if(i!=0){
        if((*v_).at(i-1) > (*v_).at(i)){
          ordered = false;
          break;
        } 
      // } 
    }

    if (!ordered) {
      std::cout << "vector desordenado";
    } else {
      for(int i =0; i<(*v_).size(); i++){
        std::cout << (*v_).at(i) << " ";
      }
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