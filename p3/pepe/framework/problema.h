
#ifndef PROBLEMA_H_
#define PROBLEMA_H_

#include<vector>
#include<utility>
#include<iostream>
#include"Solucion.h"
using namespace std;

class Problema {
public:
	Problema();
	virtual ~Problema();

	virtual bool isCasoMinimo();
	virtual pair<Problema*,Problema*> descomponer();
	virtual void solver(Solucion* s);
};

#endif /* PROBLEMA_H_ */
