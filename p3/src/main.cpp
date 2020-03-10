#include <iostream>
#include <stdlib.h>
#include "../include/mergesortP.hpp"
#include "../include/mergesortS.hpp"
#include "../include/quicksortP.hpp"
#include "../include/quicksortS.hpp"
#include "../include/framework.hpp"

void fill(std::vector<int> &v, int size, int seed){
	srand(seed);
	for(int i=0; i<size; i++){
		v.push_back(rand() % 100);
	}
}



int main(int argc, char *argv[]) {

	std::vector<int> v;
	int size=(atoi(argv[1]));
	int seed=(atoi(argv[2]));

	fill(v,size,seed);
	for(int i=0; i< v.size(); i++){
		std::cout << v[i] << " ";
	}
	std::cout << "\n";


	problem* p = new mergesortP(v);
	solution* s = new mergesortS();
	framework* f = new framework();

	f->divideyVenceras(p,s);
	std::cout << "\nResultado merge sort\n";
	s->solve_s();
	delete p;
	delete s;
	p = new quicksortP(&v,0,9);
	s = new quicksortS();
	f->divideyVenceras(p,s);
	std::cout << "\nResultado quicksort\n";
	s->solve_s();
}