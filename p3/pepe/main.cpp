
#ifndef MAIN_
#define MAIN_

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include"framework/Framework.h"
#include"mergesort/mergesortP.h"
#include"mergesort/mergesortS.h"
#include"quicksort/quicksortP.h"
#include"quicksort/quicksortS.h"
using namespace std;


int main(int argc, char* argv[]){
  std::vector<int> array(argc-1);

	if (argc < 2) {
		cout << "\nNúmero de parametros incorrecto. Encontrado " << argc-1 << " requerido 1."<< endl;
		exit(-1);
	} else {
    for(int i = 1; i < argc; i++){
      array[i-1] = atoi(argv[i]);
      // std::cout << array[i-1];
    }
    // std::cout << array.size();
  }
	Problema* problema = new MergesortP(array);
	Solucion* solucion = new MergesortS();
	Framework* framework = new Framework();

	framework->divideyVenceras(problema, solucion);
	cout << "\nResultado Mergesort:" << endl;
	solucion->resolver();
  int size = array.size();
  problema = new QuicksortP(&array,0,size - 1);
  solucion = new QuicksortS();

  framework->divideyVenceras(problema, solucion);
  cout << "\nResultado Quicksort:" << endl;
  solucion->resolver();

};

#endif /* MAIN_ */
