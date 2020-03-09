
#ifndef FIBONACCIS_H_
#define FIBONACCIS_H_

#include "../framework/Solucion.h"

class FibonacciS: public Solucion {
public:
	FibonacciS();
	virtual ~FibonacciS();

	void resolver();
	void mezcla(pair<Solucion*,Solucion*>);
	Solucion* getInstance();

	void setValor(int);

private:
	int _n;

};

#endif /* FIBONACCIS_H_ */
