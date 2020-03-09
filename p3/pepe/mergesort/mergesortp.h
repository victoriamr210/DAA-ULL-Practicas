
#pragma once
#include "../framework/Problema.h"
#include "mergesorts.h"

class MergesortP: public Problema {
public:
	MergesortP(std::vector<int> array);
	virtual ~MergesortP();

	bool isCasoMinimo();
	pair<Problema*,Problema*> descomponer();
	void solver(Solucion* s);

private:
  std::vector<int> _array;
};
