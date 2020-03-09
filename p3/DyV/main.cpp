
#ifndef MAIN_
#define MAIN_

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include"framework/Framework.h"
#include"examples/FibonacciP.h"
#include"examples/FibonacciS.h"
using namespace std;


int main(int argc, char* argv[]){
	if (argc != 2) {
		cout << "\nNúmero de parametros incorrecto. Encontrado " << argc-1 << " requerido 1."<< endl;
		exit(-1);
	}

	Problema* problema = new FibonacciP(atoi(argv[1]));
	Solucion* solucion = new FibonacciS();
	Framework* framework = new Framework();

	framework->divideyVenceras(problema, solucion);
	cout << "\nResultado:" << endl;
	solucion->resolver();

};

#endif /* MAIN_ */
