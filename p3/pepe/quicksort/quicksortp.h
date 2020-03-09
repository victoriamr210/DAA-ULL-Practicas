
#pragma once
#include "../framework/Problema.h"
#include "quicksorts.h"

class QuicksortP: public Problema {
public:
	QuicksortP(std::vector<int>* array, int low, int high);
	virtual ~QuicksortP();

	bool isCasoMinimo();
	pair<Problema*,Problema*> descomponer();
	void solver(Solucion* s);

private:
  std::vector<int>* _array;
  int _low;
  int _high;
};
