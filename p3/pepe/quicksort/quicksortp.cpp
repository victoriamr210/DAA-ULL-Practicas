
#include "quicksortp.h"

QuicksortP::QuicksortP(std::vector<int>* array, int low, int high) : Problema::Problema() {
	_array = array;
  _low = low;
  _high = high;
}

QuicksortP::~QuicksortP() {

}

bool QuicksortP::isCasoMinimo() {
	return (_low >= _high);
}

pair<Problema*,Problema*> QuicksortP::descomponer() {
	pair<Problema*,Problema*> subProblemas;
  int pivote = _array->at(_low); // pivot
  int indiceMenores = _low + 1; // Indice de los numeros menores a pivote
  int indiceMayores = _high;
  while (indiceMenores <= indiceMayores){
    while ( indiceMenores <= indiceMayores && _array->at(indiceMenores) <= pivote ){
      indiceMenores++;
    }
    while ( indiceMenores <= indiceMayores && pivote <= _array->at(indiceMayores) ){
      indiceMayores--;
    }
    if (indiceMenores < indiceMayores){
      swap(_array->at(indiceMenores),_array->at(indiceMayores));
    }
  }
  swap(_array->at(indiceMayores), _array->at(_low));
  int pivotePos = indiceMayores;
  subProblemas.first = new QuicksortP(_array,_low,pivotePos - 1);
	subProblemas.second = new QuicksortP(_array,pivotePos + 1,_high);
	return subProblemas;
}

void QuicksortP::solver(Solucion* s) {
	((QuicksortS*)s)->setValor(_array);
}
