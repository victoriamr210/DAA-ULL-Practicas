#include "../include/quicksortP.hpp"
#include "../include/quicksortS.hpp"

quicksortP::quicksortP(std::vector<int>* v, int min, int max){
  v_ = v;
  min_ = min;
  max_ = max;
}

bool quicksortP::isMin(void){
  return (min_ >= max_);
}

std::pair<problem *, problem *> quicksortP::decompose(void){
  // std::cout << "decompose\n";
  std::pair<problem*,problem*> subP;
  int pivote = v_->at(min_); // pivot
  int lessIndex = min_ + 1;  // Indice de los numeros menores a pivote
  int greaterIndex = max_;
  while (lessIndex <= greaterIndex){
    while (lessIndex <= greaterIndex && v_->at(lessIndex) <= pivote){
      lessIndex++;
    }

    while (lessIndex <= greaterIndex && pivote <= v_->at(greaterIndex)){
      greaterIndex--;
    }
    if (lessIndex < greaterIndex){
      std::swap(v_->at(lessIndex), v_->at(greaterIndex));
    }
  }

  std::swap(v_->at(greaterIndex), v_->at(min_));
  int pivotePos = greaterIndex;
  subP.first = new quicksortP(v_, min_, pivotePos - 1);
  subP.second = new quicksortP(v_, pivotePos + 1, max_);
  return subP;
}

void quicksortP::solve(solution* s){
  // std::cout << "solve\n";
  ((quicksortS*)s)->set(v_);
}

