
#include<iostream>
#include "quicksorts.h"

QuicksortS::QuicksortS() : Solucion::Solucion() {
}

QuicksortS::~QuicksortS() {
}


void QuicksortS::resolver() {
  for(int i = 0; i < (*_array).size();i++){
  	cout << (*_array).at(i) <<  "  | ";
  }
  cout << endl;
}

void QuicksortS::mezcla(pair<Solucion*,Solucion*> subSoluciones) {
  _array = ((QuicksortS*)subSoluciones.first)->_array;
}

Solucion* QuicksortS::getInstance() {
	return new QuicksortS();
}

void QuicksortS::setValor(std::vector<int>* array) {
	_array = array;
}
