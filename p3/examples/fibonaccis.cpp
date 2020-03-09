
#include<iostream>
#include "FibonacciS.h"

FibonacciS::FibonacciS() : Solucion::Solucion() {
}

FibonacciS::~FibonacciS() {
}


void FibonacciS::resolver() {
	cout << _n << endl;
}

void FibonacciS::mezcla(pair<Solucion*,Solucion*> subSoluciones) {
	int n1 = (((FibonacciS*)subSoluciones.first))->_n;
	int n2 = ((FibonacciS*)subSoluciones.second)->_n;
	_n = n1+n2;
}

Solucion* FibonacciS::getInstance() {
	return new FibonacciS();
}

void FibonacciS::setValor(int n) {
	_n = n;
}
