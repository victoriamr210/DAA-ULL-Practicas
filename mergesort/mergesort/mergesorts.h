#pragma once
#include <vector>
#include "../framework/Solucion.h"

class MergesortS: public Solucion {
public:
	MergesortS();
	virtual ~MergesortS();

	void resolver();
	void mezcla(pair<Solucion*,Solucion*>);
	Solucion* getInstance();

	void setValor(std::vector<int> array);

private:
  std::vector<int> _array;

};
