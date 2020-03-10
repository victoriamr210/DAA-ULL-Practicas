
#pragma once
#include "../framework/Problema.h"
#include "quicksorts.h"

class QuicksortP: public Problema {
public:
	QuicksortP(std::vector<int> array);
	virtual ~QuicksortP();

	bool isCasoMinimo();
	pair<Problema*,Problema*> descomponer();
	void solver(Solucion* s);

private:
  std::vector<int> _array;
};
