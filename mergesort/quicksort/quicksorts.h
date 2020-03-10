#pragma once
#include <vector>
#include "../framework/Solucion.h"

class QuicksortS: public Solucion {
public:
	QuicksortS();
	virtual ~QuicksortS();

	void resolver();
	void mezcla(pair<Solucion*,Solucion*>);
	Solucion* getInstance();

	void setValor(std::vector<int> array);

private:
  std::vector<int> _array;
  int _pivote;
};
