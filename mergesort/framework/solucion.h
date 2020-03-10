#ifndef SOLUCION_H_
#define SOLUCION_H_

#include<vector>
#include <utility>
#include<iostream>
using namespace std;

class Solucion {
public:
	Solucion();
	virtual ~Solucion();

	virtual void resolver();
	virtual void mezcla(pair<Solucion*,Solucion*>);
	virtual Solucion* getInstance();
};

#endif /* SOLUCION_H_ */
