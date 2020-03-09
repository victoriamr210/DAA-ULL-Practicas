
#include<iostream>
#include "mergesorts.h"

MergesortS::MergesortS() : Solucion::Solucion() {
}

MergesortS::~MergesortS() {
}


void MergesortS::resolver() {
  for(int i = 0; i < _array.size();i++){
  	cout << _array[i] <<  "  | ";
  }
  cout << endl;
}

void MergesortS::mezcla(pair<Solucion*,Solucion*> subSoluciones) {
	std::vector<int> mitad1 = ((MergesortS*)subSoluciones.first)->_array;
	std::vector<int> mitad2 = ((MergesortS*)subSoluciones.second)->_array;
  int i = 0; // indice mitad1
  int j = 0; // indice mitad2
  int k = 0; // indice _array
    _array.resize(mitad1.size() + mitad2.size());
  while (i < mitad1.size() && j < mitad2.size()) {
    if (mitad1[i] <= mitad2[j]) {
      _array[k] = mitad1[i];
      i++;
    } else {
      _array[k] = mitad2[j];
      j++;
    }
    k++;
  }
  while (i < mitad1.size()) {
     _array[k] = mitad1[i];
     i++;
     k++;
  }
  while (j < mitad2.size()) {
     _array[k] = mitad2[j];
     j++;
     k++;
  }
}

Solucion* MergesortS::getInstance() {
	return new MergesortS();
}

void MergesortS::setValor(std::vector<int> array) {
	_array = array;
}
