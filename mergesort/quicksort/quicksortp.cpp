
#include "quicksortp.h"

QuicksortP::QuicksortP(std::vector<int> array) : Problema::Problema() {
	_array = array;
}

QuicksortP::~QuicksortP() {

}

bool QuicksortP::isCasoMinimo() {
	return (_array.size() < 2);
}

pair<Problema*,Problema*> QuicksortP::descomponer() {
	pair<Problema*,Problema*> subProblemas;
  int pivot = _array[0]; // pivot
  int indiceMenores = 1; // Indice de los numeros menores a pivote
  int indiceMayores = _array.size();
  while (indiceMenores < indiceMayores){
    if (_array[indiceMenores] < pivote){
      indiceMenores++;
    } else if (pivote < _array[indiceMayores]){
      indiceMayores--;
    } else if (indiceMenores < indiceMayores){
      swap(_array[indiceMenores++,indiceMayores--]);
    }
  }
  swap(_array[i], _array[0]);
  std::vector<int> tempArray;
  for(int i = 0; i < indiceMenores ; i++){
     tempArray.push_back(_array[i]);
  }
  subProblemas.first = new QuicksortP(tempArray);
  tempArray.clear();
  for(int i = indiceMenores + 1; i < _array.size(); i++){
    tempArray.push_back(_array[i]);
  }
	subProblemas.second = new QuicksortP(tempArray);
	return subProblemas;
}

void QuicksortP::solver(Solucion* s) {
	((QuicksortS*)s)->setValor(_array);
}
