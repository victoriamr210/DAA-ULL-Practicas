
#include "mergesortp.h"

MergesortP::MergesortP(std::vector<int> array) : Problema::Problema() {
	_array = array;
}

MergesortP::~MergesortP() {

}

bool MergesortP::isCasoMinimo() {
	return (_array.size() < 2);
}

pair<Problema*,Problema*> MergesortP::descomponer() {
	pair<Problema*,Problema*> subProblemas;
  std::vector<int> tempArray;
  for(int i = 0; i < _array.size() / 2; i++){
    tempArray.push_back(_array[i]);
  }
  subProblemas.first = new MergesortP(tempArray);
  tempArray.clear();
  for(int i = _array.size() / 2; i < _array.size(); i++){
    tempArray.push_back(_array[i]);
  }
	subProblemas.second = new MergesortP(tempArray);
	return subProblemas;
}

void MergesortP::solver(Solucion* s) {
	((MergesortS*)s)->setValor(_array);
}
